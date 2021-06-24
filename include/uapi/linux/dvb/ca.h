<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ WITH Linux-syscall-note */
/*
 * ca.h
 *
 * Copyright (C) 2000 Ralph  Metzler <ralph@convergence.de>
 *                  & Marcus Metzler <marcus@convergence.de>
 *                    क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Lesser Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#अगर_अघोषित _DVBCA_H_
#घोषणा _DVBCA_H_

/**
 * काष्ठा ca_slot_info - CA slot पूर्णांकerface types and info.
 *
 * @num:	slot number.
 * @type:	slot type.
 * @flags:	flags applicable to the slot.
 *
 * This काष्ठा stores the CA slot inक्रमmation.
 *
 * @type can be:
 *
 *	- %CA_CI - CI high level पूर्णांकerface;
 *	- %CA_CI_LINK - CI link layer level पूर्णांकerface;
 *	- %CA_CI_PHYS - CI physical layer level पूर्णांकerface;
 *	- %CA_DESCR - built-in descrambler;
 *	- %CA_SC -simple smart card पूर्णांकerface.
 *
 * @flags can be:
 *
 *	- %CA_CI_MODULE_PRESENT - module (or card) inserted;
 *	- %CA_CI_MODULE_READY - module is पढ़ोy क्रम usage.
 */

काष्ठा ca_slot_info अणु
	पूर्णांक num;
	पूर्णांक type;
#घोषणा CA_CI            1
#घोषणा CA_CI_LINK       2
#घोषणा CA_CI_PHYS       4
#घोषणा CA_DESCR         8
#घोषणा CA_SC          128

	अचिन्हित पूर्णांक flags;
#घोषणा CA_CI_MODULE_PRESENT 1
#घोषणा CA_CI_MODULE_READY   2
पूर्ण;


/**
 * काष्ठा ca_descr_info - descrambler types and info.
 *
 * @num:	number of available descramblers (keys).
 * @type:	type of supported scrambling प्रणाली.
 *
 * Identअगरies the number of descramblers and their type.
 *
 * @type can be:
 *
 *	- %CA_ECD - European Common Descrambler (ECD) hardware;
 *	- %CA_NDS - Videoguard (NDS) hardware;
 *	- %CA_DSS - Distributed Sample Scrambling (DSS) hardware.
 */
काष्ठा ca_descr_info अणु
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक type;
#घोषणा CA_ECD           1
#घोषणा CA_NDS           2
#घोषणा CA_DSS           4
पूर्ण;

/**
 * काष्ठा ca_caps - CA slot पूर्णांकerface capabilities.
 *
 * @slot_num:	total number of CA card and module slots.
 * @slot_type:	biपंचांगap with all supported types as defined at
 *		&काष्ठा ca_slot_info (e. g. %CA_CI, %CA_CI_LINK, etc).
 * @descr_num:	total number of descrambler slots (keys)
 * @descr_type:	biपंचांगap with all supported types as defined at
 *		&काष्ठा ca_descr_info (e. g. %CA_ECD, %CA_NDS, etc).
 */
काष्ठा ca_caps अणु
	अचिन्हित पूर्णांक slot_num;
	अचिन्हित पूर्णांक slot_type;
	अचिन्हित पूर्णांक descr_num;
	अचिन्हित पूर्णांक descr_type;
पूर्ण;

/**
 * काष्ठा ca_msg - a message to/from a CI-CAM
 *
 * @index:	unused
 * @type:	unused
 * @length:	length of the message
 * @msg:	message
 *
 * This काष्ठा carries a message to be send/received from a CI CA module.
 */
काष्ठा ca_msg अणु
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक length;
	अचिन्हित अक्षर msg[256];
पूर्ण;

/**
 * काष्ठा ca_descr - CA descrambler control words info
 *
 * @index: CA Descrambler slot
 * @parity: control words parity, where 0 means even and 1 means odd
 * @cw: CA Descrambler control words
 */
काष्ठा ca_descr अणु
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक parity;
	अचिन्हित अक्षर cw[8];
पूर्ण;

#घोषणा CA_RESET          _IO('o', 128)
#घोषणा CA_GET_CAP        _IOR('o', 129, काष्ठा ca_caps)
#घोषणा CA_GET_SLOT_INFO  _IOR('o', 130, काष्ठा ca_slot_info)
#घोषणा CA_GET_DESCR_INFO _IOR('o', 131, काष्ठा ca_descr_info)
#घोषणा CA_GET_MSG        _IOR('o', 132, काष्ठा ca_msg)
#घोषणा CA_SEND_MSG       _IOW('o', 133, काष्ठा ca_msg)
#घोषणा CA_SET_DESCR      _IOW('o', 134, काष्ठा ca_descr)

#अगर !defined(__KERNEL__)

/* This is needed क्रम legacy userspace support */
प्रकार काष्ठा ca_slot_info ca_slot_info_t;
प्रकार काष्ठा ca_descr_info  ca_descr_info_t;
प्रकार काष्ठा ca_caps  ca_caps_t;
प्रकार काष्ठा ca_msg ca_msg_t;
प्रकार काष्ठा ca_descr ca_descr_t;

#पूर्ण_अगर


#पूर्ण_अगर
