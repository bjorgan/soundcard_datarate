#include "audiosink.h"
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioDeviceInfo>
#include <iostream>
#include <sys/time.h>

AudioSink::AudioSink(QObject *parent) : QIODevice(parent)
{
    timer.start();
    tot_num_samples = 0;

    gettimeofday(&last_call, NULL);
}

qint64 AudioSink::writeData (char const * data, qint64 maxSize)
{
    //calculate mean effective data rates of incoming data
    tot_num_samples += maxSize;

    //for "instantaneous" data rate
    struct timeval curr_call;
    gettimeofday(&curr_call, NULL);
    double call_time = (curr_call.tv_sec - last_call.tv_sec) + (curr_call.tv_usec - last_call.tv_usec)*1.0e-06;

    //mean and "instantaneous" information
    fprintf(stderr, "%f %ld %f\n", tot_num_samples/2.0/(this->timer.elapsed()/1000.0), maxSize/2, call_time);

    last_call = curr_call;

    return maxSize;
}

Audio::Audio(QString device_name, int sample_rate, QObject *parent) : QObject(parent)
{
    //probe devices
    QList<QAudioDeviceInfo> list = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    QAudioDeviceInfo device = list[0];
    int selected_device = -1;
    for (int i=0; i < list.size(); i++) {
        if (list[i].deviceName() == device_name) {
            selected_device = i;
            break;
        }
    }
    if (selected_device == -1) {
        fprintf(stderr, "No device found\n");
        exit(1);
    }

    //set up audio format of input device
    QAudioFormat format (device.preferredFormat());
    format.setChannelCount (1);
    format.setCodec ("audio/pcm");
    format.setSampleRate (sample_rate);
    format.setSampleType (QAudioFormat::SignedInt);
    format.setSampleSize (16);
    format.setByteOrder (QAudioFormat::Endian (QSysInfo::ByteOrder));

    //send output of audio input to AudioSink
    QAudioInput *input = new QAudioInput(device, format);
    AudioSink *sink = new AudioSink();
    sink->open(QIODevice::WriteOnly | QIODevice::Unbuffered);
    input->start(sink);
}
