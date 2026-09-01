# dwm

My customized build of [dwm](https://dwm.suckless.org/).

This build is used by my Arch Linux and Debian dwm setup and contains the patches and configuration I use daily.

## Installation

Clone the repository:

```sh
git clone https://github.com/rabbi-lion/dwm.git
cd dwm
```

Build and install:

```sh
make
sudo make install
```

On a fresh system, the recommended method is to use my post-install script:

```text
https://github.com/rabbi-lion/dwm-install
```

## Features

This build includes:

- vanity gaps
- scratchpads
- swallowing
- sticky windows
- desktop toggle
- centered floating windows
- stack rotation
- clickable dwmblocks
- dwmblocks signaling

## Scratchpads

Scratchpads are integrated directly into dwm and can be toggled independently of the normal tags.

Floating scratchpads are centered automatically.

## Swallowing

Terminal windows can swallow applications launched from them.

When the child application exits, the original terminal window is restored.

## Sticky windows

Windows can be marked sticky so they remain visible when switching between tags.

## Desktop toggle

A desktop mode can temporarily hide normal client windows, providing quick access to the desktop without changing the active tag.

## Gaps

Vanity gaps provide configurable inner and outer gaps between tiled windows and the edges of the monitor.

## Floating windows

Floating windows are centered automatically when their size allows it.

## Stack rotation

The client stack can be rotated without changing the selected layout.

## dwmblocks integration

This build integrates with my `dwmblocks` configuration.

It supports:

- clickable status blocks
- block signals
- immediate status updates

My dwmblocks repository is available at:

```text
https://github.com/rabbi-lion/dwmblocks
```

Status scripts are provided by my dotfiles:

```text
https://github.com/rabbi-lion/dotfiles
```

## Configuration

dwm is configured directly in:

```text
config.h
```

After changing the configuration, rebuild and reinstall:

```sh
sudo make clean install
```

Restart dwm to apply the changes.

## Related repositories

```text
https://github.com/rabbi-lion/dwm-install
https://github.com/rabbi-lion/dotfiles
https://github.com/rabbi-lion/st
https://github.com/rabbi-lion/dwmblocks
https://github.com/rabbi-lion/nsxiv
```

## License

This repository retains the original dwm MIT/X Consortium license.

See `LICENSE` for the full license text.
