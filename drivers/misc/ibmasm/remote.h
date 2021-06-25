<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

/*
 * IBM ASM Service Processor Device Driver
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 *
 * Originally written by Pete Reynolds
 */

#अगर_अघोषित _IBMASM_REMOTE_H_
#घोषणा _IBMASM_REMOTE_H_

#समावेश <यंत्र/पन.स>

/* pci offsets */
#घोषणा CONDOR_MOUSE_DATA		0x000AC000
#घोषणा CONDOR_MOUSE_ISR_CONTROL	0x00
#घोषणा CONDOR_MOUSE_ISR_STATUS		0x04
#घोषणा CONDOR_MOUSE_Q_READER		0x08
#घोषणा CONDOR_MOUSE_Q_WRITER		0x0C
#घोषणा CONDOR_MOUSE_Q_BEGIN		0x10
#घोषणा CONDOR_MOUSE_MAX_X		0x14
#घोषणा CONDOR_MOUSE_MAX_Y		0x18

#घोषणा CONDOR_INPUT_DESKTOP_INFO	0x1F0
#घोषणा CONDOR_INPUT_DISPLAY_RESX	0x1F4
#घोषणा CONDOR_INPUT_DISPLAY_RESY	0x1F8
#घोषणा CONDOR_INPUT_DISPLAY_BITS	0x1FC
#घोषणा CONDOR_OUTPUT_VNC_STATUS	0x200

#घोषणा CONDOR_MOUSE_INTR_STATUS_MASK	0x00000001

#घोषणा INPUT_TYPE_MOUSE	0x1
#घोषणा INPUT_TYPE_KEYBOARD	0x2


/* mouse button states received from SP */
#घोषणा REMOTE_DOUBLE_CLICK	0xF0
#घोषणा REMOTE_BUTTON_LEFT	0x01
#घोषणा REMOTE_BUTTON_MIDDLE	0x02
#घोषणा REMOTE_BUTTON_RIGHT	0x04

/* size of keysym/keycode translation matricies */
#घोषणा XLATE_SIZE 256

काष्ठा mouse_input अणु
	अचिन्हित लघु	y;
	अचिन्हित लघु	x;
पूर्ण;


काष्ठा keyboard_input अणु
	अचिन्हित लघु	key_code;
	अचिन्हित अक्षर	key_flag;
	अचिन्हित अक्षर	key_करोwn;
पूर्ण;



काष्ठा remote_input अणु
	जोड़ अणु
		काष्ठा mouse_input	mouse;
		काष्ठा keyboard_input	keyboard;
	पूर्ण data;

	अचिन्हित अक्षर	type;
	अचिन्हित अक्षर	pad1;
	अचिन्हित अक्षर	mouse_buttons;
	अचिन्हित अक्षर	pad3;
पूर्ण;

#घोषणा mouse_addr(sp)		(sp->base_address + CONDOR_MOUSE_DATA)
#घोषणा display_width(sp)	(mouse_addr(sp) + CONDOR_INPUT_DISPLAY_RESX)
#घोषणा display_height(sp)	(mouse_addr(sp) + CONDOR_INPUT_DISPLAY_RESY)
#घोषणा display_depth(sp)	(mouse_addr(sp) + CONDOR_INPUT_DISPLAY_BITS)
#घोषणा desktop_info(sp)	(mouse_addr(sp) + CONDOR_INPUT_DESKTOP_INFO)
#घोषणा vnc_status(sp)		(mouse_addr(sp) + CONDOR_OUTPUT_VNC_STATUS)
#घोषणा isr_control(sp)		(mouse_addr(sp) + CONDOR_MOUSE_ISR_CONTROL)

#घोषणा mouse_पूर्णांकerrupt_pending(sp)	पढ़ोl(mouse_addr(sp) + CONDOR_MOUSE_ISR_STATUS)
#घोषणा clear_mouse_पूर्णांकerrupt(sp)	ग_लिखोl(0, mouse_addr(sp) + CONDOR_MOUSE_ISR_STATUS)
#घोषणा enable_mouse_पूर्णांकerrupts(sp)	ग_लिखोl(1, mouse_addr(sp) + CONDOR_MOUSE_ISR_CONTROL)
#घोषणा disable_mouse_पूर्णांकerrupts(sp)	ग_लिखोl(0, mouse_addr(sp) + CONDOR_MOUSE_ISR_CONTROL)

/* remote input queue operations */
#घोषणा REMOTE_QUEUE_SIZE	60

#घोषणा get_queue_ग_लिखोr(sp)	पढ़ोl(mouse_addr(sp) + CONDOR_MOUSE_Q_WRITER)
#घोषणा get_queue_पढ़ोer(sp)	पढ़ोl(mouse_addr(sp) + CONDOR_MOUSE_Q_READER)
#घोषणा set_queue_पढ़ोer(sp, पढ़ोer)	ग_लिखोl(पढ़ोer, mouse_addr(sp) + CONDOR_MOUSE_Q_READER)

#घोषणा queue_begin	(mouse_addr(sp) + CONDOR_MOUSE_Q_BEGIN)

#घोषणा get_queue_entry(sp, पढ़ो_index) \
	((व्योम*)(queue_begin + पढ़ो_index * माप(काष्ठा remote_input)))

अटल अंतरभूत पूर्णांक advance_queue_पढ़ोer(काष्ठा service_processor *sp, अचिन्हित दीर्घ पढ़ोer)
अणु
	पढ़ोer++;
	अगर (पढ़ोer == REMOTE_QUEUE_SIZE)
		पढ़ोer = 0;

	set_queue_पढ़ोer(sp, पढ़ोer);
	वापस पढ़ोer;
पूर्ण

#घोषणा NO_KEYCODE 0
#घोषणा KEY_SYM_BK_SPC   0xFF08
#घोषणा KEY_SYM_TAB      0xFF09
#घोषणा KEY_SYM_ENTER    0xFF0D
#घोषणा KEY_SYM_SCR_LOCK 0xFF14
#घोषणा KEY_SYM_ESCAPE   0xFF1B
#घोषणा KEY_SYM_HOME     0xFF50
#घोषणा KEY_SYM_LARROW   0xFF51
#घोषणा KEY_SYM_UARROW   0xFF52
#घोषणा KEY_SYM_RARROW   0xFF53
#घोषणा KEY_SYM_DARROW   0xFF54
#घोषणा KEY_SYM_PAGEUP   0xFF55
#घोषणा KEY_SYM_PAGEDOWN 0xFF56
#घोषणा KEY_SYM_END      0xFF57
#घोषणा KEY_SYM_INSERT   0xFF63
#घोषणा KEY_SYM_NUM_LOCK 0xFF7F
#घोषणा KEY_SYM_KPSTAR   0xFFAA
#घोषणा KEY_SYM_KPPLUS   0xFFAB
#घोषणा KEY_SYM_KPMINUS  0xFFAD
#घोषणा KEY_SYM_KPDOT    0xFFAE
#घोषणा KEY_SYM_KPSLASH  0xFFAF
#घोषणा KEY_SYM_KPRIGHT  0xFF96
#घोषणा KEY_SYM_KPUP     0xFF97
#घोषणा KEY_SYM_KPLEFT   0xFF98
#घोषणा KEY_SYM_KPDOWN   0xFF99
#घोषणा KEY_SYM_KP0      0xFFB0
#घोषणा KEY_SYM_KP1      0xFFB1
#घोषणा KEY_SYM_KP2      0xFFB2
#घोषणा KEY_SYM_KP3      0xFFB3
#घोषणा KEY_SYM_KP4      0xFFB4
#घोषणा KEY_SYM_KP5      0xFFB5
#घोषणा KEY_SYM_KP6      0xFFB6
#घोषणा KEY_SYM_KP7      0xFFB7
#घोषणा KEY_SYM_KP8      0xFFB8
#घोषणा KEY_SYM_KP9      0xFFB9
#घोषणा KEY_SYM_F1       0xFFBE      // 1B 5B 5B 41
#घोषणा KEY_SYM_F2       0xFFBF      // 1B 5B 5B 42
#घोषणा KEY_SYM_F3       0xFFC0      // 1B 5B 5B 43
#घोषणा KEY_SYM_F4       0xFFC1      // 1B 5B 5B 44
#घोषणा KEY_SYM_F5       0xFFC2      // 1B 5B 5B 45
#घोषणा KEY_SYM_F6       0xFFC3      // 1B 5B 31 37 7E
#घोषणा KEY_SYM_F7       0xFFC4      // 1B 5B 31 38 7E
#घोषणा KEY_SYM_F8       0xFFC5      // 1B 5B 31 39 7E
#घोषणा KEY_SYM_F9       0xFFC6      // 1B 5B 32 30 7E
#घोषणा KEY_SYM_F10      0xFFC7      // 1B 5B 32 31 7E
#घोषणा KEY_SYM_F11      0xFFC8      // 1B 5B 32 33 7E
#घोषणा KEY_SYM_F12      0xFFC9      // 1B 5B 32 34 7E
#घोषणा KEY_SYM_SHIFT    0xFFE1
#घोषणा KEY_SYM_CTRL     0xFFE3
#घोषणा KEY_SYM_ALT      0xFFE9
#घोषणा KEY_SYM_CAP_LOCK 0xFFE5
#घोषणा KEY_SYM_DELETE   0xFFFF
#घोषणा KEY_SYM_TILDE    0x60
#घोषणा KEY_SYM_BKTIC    0x7E
#घोषणा KEY_SYM_ONE      0x31
#घोषणा KEY_SYM_BANG     0x21
#घोषणा KEY_SYM_TWO      0x32
#घोषणा KEY_SYM_AT       0x40
#घोषणा KEY_SYM_THREE    0x33
#घोषणा KEY_SYM_POUND    0x23
#घोषणा KEY_SYM_FOUR     0x34
#घोषणा KEY_SYM_DOLLAR   0x24
#घोषणा KEY_SYM_FIVE     0x35
#घोषणा KEY_SYM_PERCENT  0x25
#घोषणा KEY_SYM_SIX      0x36
#घोषणा KEY_SYM_CARAT    0x5E
#घोषणा KEY_SYM_SEVEN    0x37
#घोषणा KEY_SYM_AMPER    0x26
#घोषणा KEY_SYM_EIGHT    0x38
#घोषणा KEY_SYM_STAR     0x2A
#घोषणा KEY_SYM_NINE     0x39
#घोषणा KEY_SYM_LPAREN   0x28
#घोषणा KEY_SYM_ZERO     0x30
#घोषणा KEY_SYM_RPAREN   0x29
#घोषणा KEY_SYM_MINUS    0x2D
#घोषणा KEY_SYM_USCORE   0x5F
#घोषणा KEY_SYM_EQUAL    0x2B
#घोषणा KEY_SYM_PLUS     0x3D
#घोषणा KEY_SYM_LBRKT    0x5B
#घोषणा KEY_SYM_LCURLY   0x7B
#घोषणा KEY_SYM_RBRKT    0x5D
#घोषणा KEY_SYM_RCURLY   0x7D
#घोषणा KEY_SYM_SLASH    0x5C
#घोषणा KEY_SYM_PIPE     0x7C
#घोषणा KEY_SYM_TIC      0x27
#घोषणा KEY_SYM_QUOTE    0x22
#घोषणा KEY_SYM_SEMIC    0x3B
#घोषणा KEY_SYM_COLON    0x3A
#घोषणा KEY_SYM_COMMA    0x2C
#घोषणा KEY_SYM_LT       0x3C
#घोषणा KEY_SYM_PERIOD   0x2E
#घोषणा KEY_SYM_GT       0x3E
#घोषणा KEY_SYM_BSLASH   0x2F
#घोषणा KEY_SYM_QMARK    0x3F
#घोषणा KEY_SYM_A        0x41
#घोषणा KEY_SYM_B        0x42
#घोषणा KEY_SYM_C        0x43
#घोषणा KEY_SYM_D        0x44
#घोषणा KEY_SYM_E        0x45
#घोषणा KEY_SYM_F        0x46
#घोषणा KEY_SYM_G        0x47
#घोषणा KEY_SYM_H        0x48
#घोषणा KEY_SYM_I        0x49
#घोषणा KEY_SYM_J        0x4A
#घोषणा KEY_SYM_K        0x4B
#घोषणा KEY_SYM_L        0x4C
#घोषणा KEY_SYM_M        0x4D
#घोषणा KEY_SYM_N        0x4E
#घोषणा KEY_SYM_O        0x4F
#घोषणा KEY_SYM_P        0x50
#घोषणा KEY_SYM_Q        0x51
#घोषणा KEY_SYM_R        0x52
#घोषणा KEY_SYM_S        0x53
#घोषणा KEY_SYM_T        0x54
#घोषणा KEY_SYM_U        0x55
#घोषणा KEY_SYM_V        0x56
#घोषणा KEY_SYM_W        0x57
#घोषणा KEY_SYM_X        0x58
#घोषणा KEY_SYM_Y        0x59
#घोषणा KEY_SYM_Z        0x5A
#घोषणा KEY_SYM_a        0x61
#घोषणा KEY_SYM_b        0x62
#घोषणा KEY_SYM_c        0x63
#घोषणा KEY_SYM_d        0x64
#घोषणा KEY_SYM_e        0x65
#घोषणा KEY_SYM_f        0x66
#घोषणा KEY_SYM_g        0x67
#घोषणा KEY_SYM_h        0x68
#घोषणा KEY_SYM_i        0x69
#घोषणा KEY_SYM_j        0x6A
#घोषणा KEY_SYM_k        0x6B
#घोषणा KEY_SYM_l        0x6C
#घोषणा KEY_SYM_m        0x6D
#घोषणा KEY_SYM_n        0x6E
#घोषणा KEY_SYM_o        0x6F
#घोषणा KEY_SYM_p        0x70
#घोषणा KEY_SYM_q        0x71
#घोषणा KEY_SYM_r        0x72
#घोषणा KEY_SYM_s        0x73
#घोषणा KEY_SYM_t        0x74
#घोषणा KEY_SYM_u        0x75
#घोषणा KEY_SYM_v        0x76
#घोषणा KEY_SYM_w        0x77
#घोषणा KEY_SYM_x        0x78
#घोषणा KEY_SYM_y        0x79
#घोषणा KEY_SYM_z        0x7A
#घोषणा KEY_SYM_SPACE    0x20
#पूर्ण_अगर /* _IBMASM_REMOTE_H_ */
