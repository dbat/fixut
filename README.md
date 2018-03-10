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

screenshot:

    Version: 0.0.1
    Created: 2008.07.22
    Revised: 2011.09.18

    Compiled with Borland's BCC version 5.5.1 (Freeware)

    SYNOPSYS:
        Fix broken torrent's downloaded files.

    USAGE:
        fixut.exe [ filename ] ...

    ARGUMENTS:
        filename: one or more files to be fixed
        - must be a real filename, not a wildcard
        - must have had the corresponding *.!ut file
          after processing, the *.!ut files can be safely discarded

    EXAMPLE:
        C:\> fixut.exe somefile.bin secondfile.dat third.rar
        C:\> for %f in (*.zip) do fixut.exe "%f"

    Press any key to continue..
 
