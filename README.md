# `torrent-name`

This is a small utility that can parse a `.torrent` file and extract the name of
the torrent.

## Usage

Build:

    $ git clone https://github.com/c2d7fa/torrent-name.git
    $ cd torrent-name
    $ gcc main.c -o torrent-name

Run:

    $ ./torrent-name arch.torrent
    archlinux-2020.02.01-x86_64.iso

## Tip for Deluge users

If you want a list of all the torrents in Deluge, but you can't be bothered to
learn how to do it properly (I think you can use `deluge-console` or something,
but whatever...), you can do it like this:

    $ ls ~/.config/deluge/state/*.torrent | xargs -I% ./torrent-name %

And to find torrents that are in a particular directory, say `/torrents`, but
which are not in Deluge, you can use `comm` like so:

    $ comm <(ls ~/.config/deluge/state/*.torrent | xargs -I% ./torrent-name % | sort) <(ls /torrents | sort) -3
