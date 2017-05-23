(Scribbled version of /tmp/ink_ext_XXXXXX.svg9HEYZY @ 350.00)
( unicorn.py --tab="plotter_setup" --pen-up-angle=50 --pen-down-angle=30 --start-delay=150 --stop-delay=150 --xy-feedrate=350 --z-feedrate=150 --z-height=0 --finished-height=0 --register-pen=true --x-home=0 --y-home=0 --num-copies=1 --continuous=false --pause-on-layer-change=false /tmp/ink_ext_XXXXXX.svg9HEYZY )
G21 (metric ftw)
G90 (absolute mode)
G92 X0.00 Y0.00 Z0.00 (you are here)

M300 S30 (pen down)
G4 P150 (wait 150ms)
M300 S50 (pen up)
G4 P150 (wait 150ms)
M18 (disengage drives)
M01 (Was registration test successful?)
M17 (engage drives if YES, and continue)

(Polyline consisting of 1 segments.)
G1 X-51.78 Y0.67 F350.00
M300 S30.00 (pen down)
G4 P150 (wait 150ms)
G1 X-51.02 Y7.89 F350.00
G1 X-49.75 Y14.20 F350.00
G1 X-48.00 Y19.63 F350.00
G1 X-45.82 Y24.22 F350.00
G1 X-43.24 Y28.01 F350.00
G1 X-40.31 Y31.05 F350.00
G1 X-37.05 Y33.36 F350.00
G1 X-33.52 Y34.98 F350.00
G1 X-29.74 Y35.96 F350.00
G1 X-25.76 Y36.33 F350.00
G1 X-21.62 Y36.13 F350.00
G1 X-17.35 Y35.40 F350.00
G1 X-12.99 Y34.17 F350.00
G1 X-8.58 Y32.49 F350.00
G1 X-4.16 Y30.39 F350.00
G1 X0.24 Y27.91 F350.00
G1 X4.56 Y25.09 F350.00
G1 X8.79 Y21.96 F350.00
G1 X16.76 Y14.95 F350.00
G1 X23.85 Y7.18 F350.00
G1 X26.97 Y3.10 F350.00
G1 X29.76 Y-1.05 F350.00
G1 X32.17 Y-5.23 F350.00
G1 X34.16 Y-9.42 F350.00
G1 X35.71 Y-13.57 F350.00
G1 X36.76 Y-17.64 F350.00
G1 X37.29 Y-21.59 F350.00
G1 X37.24 Y-25.39 F350.00
G1 X36.60 Y-29.00 F350.00
G1 X35.30 Y-32.39 F350.00
G1 X30.17 Y-41.45 F350.00
G1 X23.92 Y-50.27 F350.00
G1 X20.46 Y-54.41 F350.00
G1 X16.82 Y-58.28 F350.00
G1 X13.02 Y-61.80 F350.00
G1 X9.11 Y-64.91 F350.00
G1 X5.10 Y-67.53 F350.00
G1 X1.04 Y-69.59 F350.00
G1 X-3.04 Y-71.02 F350.00
G1 X-7.12 Y-71.75 F350.00
G1 X-11.17 Y-71.71 F350.00
G1 X-15.14 Y-70.83 F350.00
G1 X-19.01 Y-69.03 F350.00
G1 X-22.75 Y-66.25 F350.00
M300 S50.00 (pen up)
G4 P150 (wait 150ms)


(end of print job)
M300 S50.00 (pen up)
G4 P150 (wait 150ms)
M300 S255 (turn off servo)
G1 X0 Y0 F350.00
G1 Z0.00 F150.00 (go up to finished level)
G1 X0.00 Y0.00 F350.00 (go home)
M18 (drives off)
