# dwm

My customized build of [dwm](https://dwm.suckless.org/).

Used by my Arch Linux and Debian dwm setup. Contains the patches and
configuration I use daily.

## Installation

```sh
git clone https://github.com/rabbi-lion/dwm.git
cd dwm
make
sudo make install
```

On a fresh system, use my post-install script instead:

```
https://github.com/rabbi-lion/dwm-install
```

## Features

- vanity gaps
- scratchpads
- swallowing
- sticky windows
- centered floating windows
- stack rotation
- clickable dwmblocks
- dwmblocks signaling

## Scratchpads

Integrated directly into dwm. Can be toggled independently of the
normal tags. Floating scratchpads are centered automatically.

## Swallowing

Terminal windows can swallow applications launched from them. When
the child application exits, the original terminal window is restored.

## Sticky windows

Windows can be marked sticky so they remain visible when switching
between tags.

## Gaps

Vanity gaps provide configurable inner and outer gaps between tiled
windows and the edges of the monitor.

## Floating windows

Floating windows are centered automatically when their size allows it.

## Stack rotation

The client stack can be rotated without changing the selected layout.

## dwmblocks integration

Integrates with my `dwmblocks` configuration:

- clickable status blocks
- block signals
- immediate status updates

My dwmblocks repository:

```
https://github.com/rabbi-lion/dwmblocks
```

Status scripts are provided by my dotfiles:

```
https://github.com/rabbi-lion/dotfiles
```

## Configuration

dwm is configured in:

```
config.h
```

After changing the configuration, rebuild and reinstall:

```sh
sudo make clean install
```

Restart dwm to apply the changes.

## Related repositories

```
https://github.com/rabbi-lion/dwm-install
https://github.com/rabbi-lion/dotfiles
https://github.com/rabbi-lion/st
https://github.com/rabbi-lion/dwmblocks
https://github.com/rabbi-lion/nsxiv
```

## License

This repository retains the original dwm MIT/X Consortium license.
See `LICENSE` for the full license text.
