# fixut
fix broken torrent download files !.ut

When uTorrent 2.2..1 crash or interrupted it sometime produces broken
downloaded files (all files downloaded completely, but split into 2 files:
filename.ext and filename.ext.!ut partial files)

This tool fix (or accuratekly: combine the content) of those files.
After fixup, the *.!ut files can be discarded

To build the tool, simply compile fixut.c with borland's bcc 5:
  bcc32 fixut.c

source code included, you may modify it as you wish.
