#!/usr/bin/tclsh

# SPDX-License-Identifier: MPL-2.0
# Copyright (C) 2025 - 2026  Andy Frank Schoknecht

package require Tk

set count "0"
set enabled "1"
set pizza "cheese"
set text "12345"

proc toggleEnabled {val} {
	# global var has to be passed explicitly?
	if {$val eq "1"} {
		set state "active"
	} else {
		set state "disabled"
	}

	# none of these can be reached
	# nice script language
	# real quick and easy
	.btnCount configure -state state
	.lblCount configure -state state
	.txt configure -state state
	.ckb configure -state state
	.rbnCheese configure -state state
	.rbnPepperoni configure -state state
	.scl configure -state state
	.pgb configure -state state
}

menu .menubar
menu .menubar.files -tearoff 0
.menubar.files add command -label "New" -underline 0 -accelerator "Ctrl+N"
.menubar.files add command -label "Open" -underline 0 -accelerator "Ctrl+O"
.menubar.files add separator
.menubar.files add command -label "Save" -underline 0 -accelerator "Ctrl+S"
.menubar.files add command -label "Save as" -underline 5 -accelerator "Shift+Ctrl+S"
.menubar.files add separator
.menubar.files add command -label "Quit" -underline 0 -accelerator "Ctrl+Q" \
	-command {exit}
.menubar add cascade -label "File" -underline 0 -menu .menubar.files

menu .menubar.help -tearoff 0
.menubar.help add command -label "About" -underline 0
.menubar add cascade -label "Help" -underline 0 -menu .menubar.help

. configure -menu .menubar

ttk::labelframe .frmTop -text "Settings (unfinished)"
ttk::checkbutton .ckbFocusable -text "Focusable" -underline 0
.ckbFocusable invoke
.ckbFocusable configure -state disabled
ttk::checkbutton .ckbEnabled -text "Enabled" -underline 0 \
	-variable enabled -onvalue "1" -offvalue "0"
.ckbEnabled invoke
ttk::checkbutton .ckbVisible -text "Visible" -underline 0
.ckbVisible invoke

ttk::labelframe .frmBottom -text "Widgets"
ttk::button .btnCount -text "Count" -command {incr count}
ttk::label .lblCount -textvariable count
ttk::entry .txt -textvariable text
ttk::checkbutton .ckb
ttk::radiobutton .rbnCheese -text "Pizza with extra cheese" \
	-variable pizza -value "cheese"
ttk::radiobutton .rbnPepperoni -text "Pizza with extra pepperoni" \
	-variable pizza -value "pepperoni"
ttk::scale .scl -from 0 -to 10 -value 5
ttk::progressbar .pgb -value 33

bind all <Alt-f> {focus .ckbFocusable}
bind all <Alt-e> {focus .ckbEnabled}
bind all <Alt-v> {focus .ckbVisible}

bind all <Control-q> {event generate . <Destroy>}

grid .ckbFocusable -in .frmTop
grid .ckbEnabled -in .frmTop
grid .ckbVisible -in .frmTop

grid .btnCount .lblCount -in .frmBottom
grid .txt -in .frmBottom
grid .ckb -in .frmBottom
grid .rbnCheese -in .frmBottom
grid .rbnPepperoni -in .frmBottom
grid .scl .pgb -in .frmBottom

grid .frmTop
grid .frmBottom
