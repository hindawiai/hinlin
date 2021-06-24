<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Trace Module (STM) infraकाष्ठाure apis
 * Copyright (C) 2014 Intel Corporation.
 */

#अगर_अघोषित _STM_H_
#घोषणा _STM_H_

#समावेश <linux/device.h>

/**
 * क्रमागत stp_packet_type - STP packets that an STM driver sends
 */
क्रमागत stp_packet_type अणु
	STP_PACKET_DATA = 0,
	STP_PACKET_FLAG,
	STP_PACKET_USER,
	STP_PACKET_MERR,
	STP_PACKET_GERR,
	STP_PACKET_TRIG,
	STP_PACKET_XSYNC,
पूर्ण;

/**
 * क्रमागत stp_packet_flags - STP packet modअगरiers
 */
क्रमागत stp_packet_flags अणु
	STP_PACKET_MARKED	= 0x1,
	STP_PACKET_TIMESTAMPED	= 0x2,
पूर्ण;

काष्ठा stp_policy;

काष्ठा sपंचांग_device;

/**
 * काष्ठा sपंचांग_data - STM device description and callbacks
 * @name:		device name
 * @sपंचांग:		पूर्णांकernal काष्ठाure, only used by sपंचांग class code
 * @sw_start:		first STP master available to software
 * @sw_end:		last STP master available to software
 * @sw_nchannels:	number of STP channels per master
 * @sw_mmiosz:		size of one channel's IO space, क्रम mmap, optional
 * @hw_override:	masters in the STP stream will not match the ones
 *			asचिन्हित by software, but are up to the STM hardware
 * @packet:		callback that sends an STP packet
 * @mmio_addr:		mmap callback, optional
 * @link:		called when a new sपंचांग_source माला_लो linked to us, optional
 * @unlink:		likewise क्रम unlinking, again optional
 * @set_options:	set device-specअगरic options on a channel
 *
 * Fill out this काष्ठाure beक्रमe calling sपंचांग_रेजिस्टर_device() to create
 * an STM device and sपंचांग_unरेजिस्टर_device() to destroy it. It will also be
 * passed back to @packet(), @mmio_addr(), @link(), @unlink() and @set_options()
 * callbacks.
 *
 * Normally, an STM device will have a range of masters available to software
 * and the rest being अटलally asचिन्हित to various hardware trace sources.
 * The क्रमmer is defined by the the range [@sw_start..@sw_end] of the device
 * description. That is, the lowest master that can be allocated to software
 * ग_लिखोrs is @sw_start and data from this ग_लिखोr will appear is @sw_start
 * master in the STP stream.
 *
 * The @packet callback should adhere to the following rules:
 *   1) it must वापस the number of bytes it consumed from the payload;
 *   2) thereक्रमe, अगर it sent a packet that करोes not have payload (like FLAG),
 *      it must वापस zero;
 *   3) अगर it करोes not support the requested packet type/flag combination,
 *      it must वापस -ENOTSUPP.
 *
 * The @unlink callback is called when there are no more active ग_लिखोrs so
 * that the master/channel can be quiesced.
 */
काष्ठा sपंचांग_data अणु
	स्थिर अक्षर		*name;
	काष्ठा sपंचांग_device	*sपंचांग;
	अचिन्हित पूर्णांक		sw_start;
	अचिन्हित पूर्णांक		sw_end;
	अचिन्हित पूर्णांक		sw_nchannels;
	अचिन्हित पूर्णांक		sw_mmiosz;
	अचिन्हित पूर्णांक		hw_override;
	sमाप_प्रकार			(*packet)(काष्ठा sपंचांग_data *, अचिन्हित पूर्णांक,
					  अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
					  अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
					  स्थिर अचिन्हित अक्षर *);
	phys_addr_t		(*mmio_addr)(काष्ठा sपंचांग_data *, अचिन्हित पूर्णांक,
					     अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
	पूर्णांक			(*link)(काष्ठा sपंचांग_data *, अचिन्हित पूर्णांक,
					अचिन्हित पूर्णांक);
	व्योम			(*unlink)(काष्ठा sपंचांग_data *, अचिन्हित पूर्णांक,
					  अचिन्हित पूर्णांक);
	दीर्घ			(*set_options)(काष्ठा sपंचांग_data *, अचिन्हित पूर्णांक,
					       अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
					       अचिन्हित दीर्घ);
पूर्ण;

पूर्णांक sपंचांग_रेजिस्टर_device(काष्ठा device *parent, काष्ठा sपंचांग_data *sपंचांग_data,
			काष्ठा module *owner);
व्योम sपंचांग_unरेजिस्टर_device(काष्ठा sपंचांग_data *sपंचांग_data);

काष्ठा sपंचांग_source_device;

/**
 * काष्ठा sपंचांग_source_data - STM source device description and callbacks
 * @name:	device name, will be used क्रम policy lookup
 * @src:	पूर्णांकernal काष्ठाure, only used by sपंचांग class code
 * @nr_chans:	number of channels to allocate
 * @link:	called when this source माला_लो linked to an STM device
 * @unlink:	called when this source is about to get unlinked from its STM
 *
 * Fill in this काष्ठाure beक्रमe calling sपंचांग_source_रेजिस्टर_device() to
 * रेजिस्टर a source device. Also pass it to unरेजिस्टर and ग_लिखो calls.
 */
काष्ठा sपंचांग_source_data अणु
	स्थिर अक्षर		*name;
	काष्ठा sपंचांग_source_device *src;
	अचिन्हित पूर्णांक		percpu;
	अचिन्हित पूर्णांक		nr_chans;
	पूर्णांक			(*link)(काष्ठा sपंचांग_source_data *data);
	व्योम			(*unlink)(काष्ठा sपंचांग_source_data *data);
पूर्ण;

पूर्णांक sपंचांग_source_रेजिस्टर_device(काष्ठा device *parent,
			       काष्ठा sपंचांग_source_data *data);
व्योम sपंचांग_source_unरेजिस्टर_device(काष्ठा sपंचांग_source_data *data);

पूर्णांक notrace sपंचांग_source_ग_लिखो(काष्ठा sपंचांग_source_data *data, अचिन्हित पूर्णांक chan,
			     स्थिर अक्षर *buf, माप_प्रकार count);

#पूर्ण_अगर /* _STM_H_ */
