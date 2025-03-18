import sys
import os

import can


def covert(log_file, blf_file):
    with open(log_file, 'r') as f_in:
        log_in = can.io.CanutilsLogReader(file=f_in)

        with open(blf_file, 'wb+') as f_out:
            log_out = can.io.BLFWriter(f_out)
            for msg in log_in:
                log_out.on_message_received(msg)
            log_out.stop()


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 can_convert.py <log_file> <blf_file>")
        exit(1)
    if not os.path.isfile(sys.argv[1]):
        print("log file not exist: "+sys.argv[1])
        exit(1)
    if os.path.isfile(sys.argv[2]):
        print("blf file is alreadly existed: "+sys.argv[2])
        exit(1)
    covert(sys.argv[1], sys.argv[2])