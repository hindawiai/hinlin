<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */

#अगर_अघोषित __HGSMI_CHANNELS_H__
#घोषणा __HGSMI_CHANNELS_H__

/*
 * Each channel has an 8 bit identअगरier. There are a number of predefined
 * (hardcoded) channels.
 *
 * HGSMI_CH_HGSMI channel can be used to map a string channel identअगरier
 * to a मुक्त 16 bit numerical value. values are allocated in range
 * [HGSMI_CH_STRING_FIRST;HGSMI_CH_STRING_LAST].
 */

/* A reserved channel value */
#घोषणा HGSMI_CH_RESERVED				0x00
/* HGCMI: setup and configuration */
#घोषणा HGSMI_CH_HGSMI					0x01
/* Graphics: VBVA */
#घोषणा HGSMI_CH_VBVA					0x02
/* Graphics: Seamless with a single guest region */
#घोषणा HGSMI_CH_SEAMLESS				0x03
/* Graphics: Seamless with separate host winकरोws */
#घोषणा HGSMI_CH_SEAMLESS2				0x04
/* Graphics: OpenGL HW acceleration */
#घोषणा HGSMI_CH_OPENGL					0x05

/* The first channel index to be used क्रम string mappings (inclusive) */
#घोषणा HGSMI_CH_STRING_FIRST				0x20
/* The last channel index क्रम string mappings (inclusive) */
#घोषणा HGSMI_CH_STRING_LAST				0xff

#पूर्ण_अगर
