<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित US122L_H
#घोषणा US122L_H


काष्ठा us122l अणु
	काष्ठा usb_device	*dev;
	पूर्णांक			card_index;
	पूर्णांक			stride;
	काष्ठा usb_stream_kernel sk;

	काष्ठा mutex		mutex;
	काष्ठा file		*first;
	अचिन्हित		second_periods_polled;
	काष्ठा file		*master;
	काष्ठा file		*slave;
	काष्ठा list_head	midi_list;

	atomic_t		mmap_count;

	bool			is_us144;
पूर्ण;


#घोषणा US122L(c) ((काष्ठा us122l *)(c)->निजी_data)

#घोषणा NAME_ALLCAPS "US-122L"

#घोषणा USB_ID_US122L 0x800E
#घोषणा USB_ID_US144 0x800F
#घोषणा USB_ID_US122MKII 0x8021
#घोषणा USB_ID_US144MKII 0x8020

#पूर्ण_अगर
