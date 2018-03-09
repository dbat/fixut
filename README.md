# fixut
fix broken torrent download files !.ut

when uTorrent crash or interrupted it usually left broken downloaded files
(all files downloaded but split into 2 files: filename.ext and filename.ext.!ut)

this tool fix (or accuratekly: combine the content) of those file
after fixup, the *.!ut files can be discarded

to build de tool, simply compile fixut.c with borland's bcc 5:
  bcc32 fixut.c

source code included, you may modify it as you wish.
