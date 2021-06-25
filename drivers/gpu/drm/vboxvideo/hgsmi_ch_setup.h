<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */

#अगर_अघोषित __HGSMI_CH_SETUP_H__
#घोषणा __HGSMI_CH_SETUP_H__

/*
 * Tell the host the location of hgsmi_host_flags काष्ठाure, where the host
 * can ग_लिखो inक्रमmation about pending buffers, etc, and which can be quickly
 * polled by the guest without a need to port IO.
 */
#घोषणा HGSMI_CC_HOST_FLAGS_LOCATION 0

काष्ठा hgsmi_buffer_location अणु
	u32 buf_location;
	u32 buf_len;
पूर्ण __packed;

/* HGSMI setup and configuration data काष्ठाures. */

#घोषणा HGSMIHOSTFLAGS_COMMANDS_PENDING    0x01u
#घोषणा HGSMIHOSTFLAGS_IRQ                 0x02u
#घोषणा HGSMIHOSTFLAGS_VSYNC               0x10u
#घोषणा HGSMIHOSTFLAGS_HOTPLUG             0x20u
#घोषणा HGSMIHOSTFLAGS_CURSOR_CAPABILITIES 0x40u

काष्ठा hgsmi_host_flags अणु
	u32 host_flags;
	u32 reserved[3];
पूर्ण __packed;

#पूर्ण_अगर
