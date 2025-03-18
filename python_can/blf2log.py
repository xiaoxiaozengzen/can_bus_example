import sys
import os
import time

import can


def covert(blf_file, log_file):
    with open(blf_file, 'rb') as f_in:
        log_in = can.io.BLFReader(f_in)

        with open(log_file, 'w') as f_out:
            log_out = can.io.CanutilsLogWriter(f_out)
            for msg in log_in:
                msg.channel = 'can{}'.format(msg.channel)
                log_out.on_message_received(msg)
            log_out.stop()


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 can_convert.py <blf_file> <log_file>")
        exit(1)
    if not os.path.isfile(sys.argv[1]):
        print("blf file not exist: "+sys.argv[1])
        exit(1)
    if os.path.isfile(sys.argv[2]):
        print("log file is alreadly existed: "+sys.argv[2])
        exit(1)
    covert(sys.argv[1], sys.argv[2])