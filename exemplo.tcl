#!/usr/bin/wish
label .l -text "Digite alguma coisa:"
entry .e -textvariable texto
button .b -text "Clique aqui" -command  {tk_dialog .dlg_msg "Voce Digitou" $texto info 0 OK}
pack .l .e .b
