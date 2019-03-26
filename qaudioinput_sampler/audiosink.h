#include <QIODevice>
#include <QElapsedTimer>
#include <QObject>

/**
 * Receives audio samples and prints effective data rates
 * to standard output. Connect to an QAudioInput.
 **/
class AudioSink : public QIODevice
{
    Q_OBJECT
    public:
        AudioSink(QObject *parent = NULL);
    protected:
        /**
         * Receive data, print effective data rates to standard output.
         */
        qint64 writeData (char const * data, qint64 maxSize) override;
        /**
         * Had to be reimplemented since readData is abstract in QIODevice.
         **/
        qint64 readData (char*, qint64) override {return -1;};
    private:
        //timer for entire program duration, for mean effective data rate
        QElapsedTimer timer;
        //total number of samples throughout entire program duration
        long tot_num_samples;
        //time of last call to writeData, for calculation of more instantaneous rates
        struct timeval last_call;
};

/**
 * Hooks up a QAudioInput to an AudioSink.
 **/
class Audio : public QObject
{
    Q_OBJECT
    public:
        Audio(QString device_name, int sample_rate, QObject *parent = NULL);
};
