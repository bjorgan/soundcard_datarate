#include "audiosink.h"
#include <QCoreApplication>
#include <string>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s device_name (see arecord -L) sample_rate\n", argv[0]);
        exit(1);
    }

    QCoreApplication app(argc, argv);
    Audio audio(argv[1], std::stoi(argv[2]));
    return app.exec();
}

