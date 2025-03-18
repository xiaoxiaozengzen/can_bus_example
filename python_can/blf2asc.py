import sys
import os

import can


def covert(blf_file, asc_file):
    with open(blf_file, 'rb') as f_in:
        log_in = can.io.BLFReader(f_in)

        with open(asc_file, 'w') as f_out:
            log_out = can.io.ASCWriter(f_out)
            for msg in log_in:
                log_out.on_message_received(msg)
            log_out.stop()


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 can_convert.py <blf_file> <asc_file>")
        exit(1)
    if not os.path.isfile(sys.argv[1]):
        print("blf file not exist: "+sys.argv[1])
        exit(1)
    if os.path.isfile(sys.argv[2]):
        print("asc file is alreadly existed: "+sys.argv[2])
        exit(1)
    covert(sys.argv[1], sys.argv[2])