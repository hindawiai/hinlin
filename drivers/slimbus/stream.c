<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018, Linaro Limited

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/slimbus.h>
#समावेश <uapi/sound/asound.h>
#समावेश "slimbus.h"

/**
 * काष्ठा segdist_code - Segment Distributions code from
 *	Table 20 of SLIMbus Specs Version 2.0
 *
 * @ratem: Channel Rate Multipler(Segments per Superframe)
 * @seg_पूर्णांकerval: Number of slots between the first Slot of Segment
 *		and the first slot of the next  consecutive Segment.
 * @segdist_code: Segment Distribution Code SD[11:0]
 * @seg_offset_mask: Segment offset mask in SD[11:0]
 * @segdist_codes: List of all possible Segmet Distribution codes.
 */
अटल स्थिर काष्ठा segdist_code अणु
	पूर्णांक ratem;
	पूर्णांक seg_पूर्णांकerval;
	पूर्णांक segdist_code;
	u32 seg_offset_mask;

पूर्ण segdist_codes[] = अणु
	अणु1,	1536,	0x200,	 0xdffपूर्ण,
	अणु2,	768,	0x100,	 0xcffपूर्ण,
	अणु4,	384,	0x080,	 0xc7fपूर्ण,
	अणु8,	192,	0x040,	 0xc3fपूर्ण,
	अणु16,	96,	0x020,	 0xc1fपूर्ण,
	अणु32,	48,	0x010,	 0xc0fपूर्ण,
	अणु64,	24,	0x008,	 0xc07पूर्ण,
	अणु128,	12,	0x004,	 0xc03पूर्ण,
	अणु256,	6,	0x002,	 0xc01पूर्ण,
	अणु512,	3,	0x001,	 0xc00पूर्ण,
	अणु3,	512,	0xe00,	 0x1ffपूर्ण,
	अणु6,	256,	0xd00,	 0x0ffपूर्ण,
	अणु12,	128,	0xc80,	 0x07fपूर्ण,
	अणु24,	64,	0xc40,	 0x03fपूर्ण,
	अणु48,	32,	0xc20,	 0x01fपूर्ण,
	अणु96,	16,	0xc10,	 0x00fपूर्ण,
	अणु192,	8,	0xc08,	 0x007पूर्ण,
	अणु364,	4,	0xc04,	 0x003पूर्ण,
	अणु768,	2,	0xc02,	 0x001पूर्ण,
पूर्ण;

/*
 * Presence Rate table क्रम all Natural Frequencies
 * The Presence rate of a स्थिरant bitrate stream is mean flow rate of the
 * stream expressed in occupied Segments of that Data Channel per second.
 * Table 66 from SLIMbus 2.0 Specs
 *
 * Index of the table corresponds to Presence rate code क्रम the respective rate
 * in the table.
 */
अटल स्थिर पूर्णांक slim_presence_rate_table[] = अणु
	0, /* Not Indicated */
	12000,
	24000,
	48000,
	96000,
	192000,
	384000,
	768000,
	0, /* Reserved */
	110250,
	220500,
	441000,
	882000,
	176400,
	352800,
	705600,
	4000,
	8000,
	16000,
	32000,
	64000,
	128000,
	256000,
	512000,
पूर्ण;

/**
 * slim_stream_allocate() - Allocate a new SLIMbus Stream
 * @dev:Slim device to be associated with
 * @name: name of the stream
 *
 * This is very first call क्रम SLIMbus streaming, this API will allocate
 * a new SLIMbus stream and वापस a valid stream runसमय poपूर्णांकer क्रम client
 * to use it in subsequent stream apis. state of stream is set to ALLOCATED
 *
 * Return: valid poपूर्णांकer on success and error code on failure.
 * From ASoC DPCM framework, this state is linked to startup() operation.
 */
काष्ठा slim_stream_runसमय *slim_stream_allocate(काष्ठा slim_device *dev,
						 स्थिर अक्षर *name)
अणु
	काष्ठा slim_stream_runसमय *rt;

	rt = kzalloc(माप(*rt), GFP_KERNEL);
	अगर (!rt)
		वापस ERR_PTR(-ENOMEM);

	rt->name = kaप्र_लिखो(GFP_KERNEL, "slim-%s", name);
	अगर (!rt->name) अणु
		kमुक्त(rt);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	rt->dev = dev;
	spin_lock(&dev->stream_list_lock);
	list_add_tail(&rt->node, &dev->stream_list);
	spin_unlock(&dev->stream_list_lock);

	वापस rt;
पूर्ण
EXPORT_SYMBOL_GPL(slim_stream_allocate);

अटल पूर्णांक slim_connect_port_channel(काष्ठा slim_stream_runसमय *stream,
				     काष्ठा slim_port *port)
अणु
	काष्ठा slim_device *sdev = stream->dev;
	u8 wbuf[2];
	काष्ठा slim_val_inf msg = अणु0, 2, शून्य, wbuf, शून्यपूर्ण;
	u8 mc = SLIM_MSG_MC_CONNECT_SOURCE;
	DEFINE_SLIM_LDEST_TXN(txn, mc, 6, stream->dev->laddr, &msg);

	अगर (port->direction == SLIM_PORT_SINK)
		txn.mc = SLIM_MSG_MC_CONNECT_SINK;

	wbuf[0] = port->id;
	wbuf[1] = port->ch.id;
	port->ch.state = SLIM_CH_STATE_ASSOCIATED;
	port->state = SLIM_PORT_UNCONFIGURED;

	वापस slim_करो_transfer(sdev->ctrl, &txn);
पूर्ण

अटल पूर्णांक slim_disconnect_port(काष्ठा slim_stream_runसमय *stream,
				काष्ठा slim_port *port)
अणु
	काष्ठा slim_device *sdev = stream->dev;
	u8 wbuf[1];
	काष्ठा slim_val_inf msg = अणु0, 1, शून्य, wbuf, शून्यपूर्ण;
	u8 mc = SLIM_MSG_MC_DISCONNECT_PORT;
	DEFINE_SLIM_LDEST_TXN(txn, mc, 5, stream->dev->laddr, &msg);

	wbuf[0] = port->id;
	port->ch.state = SLIM_CH_STATE_DISCONNECTED;
	port->state = SLIM_PORT_DISCONNECTED;

	वापस slim_करो_transfer(sdev->ctrl, &txn);
पूर्ण

अटल पूर्णांक slim_deactivate_हटाओ_channel(काष्ठा slim_stream_runसमय *stream,
					  काष्ठा slim_port *port)
अणु
	काष्ठा slim_device *sdev = stream->dev;
	u8 wbuf[1];
	काष्ठा slim_val_inf msg = अणु0, 1, शून्य, wbuf, शून्यपूर्ण;
	u8 mc = SLIM_MSG_MC_NEXT_DEACTIVATE_CHANNEL;
	DEFINE_SLIM_LDEST_TXN(txn, mc, 5, stream->dev->laddr, &msg);
	पूर्णांक ret;

	wbuf[0] = port->ch.id;
	ret = slim_करो_transfer(sdev->ctrl, &txn);
	अगर (ret)
		वापस ret;

	txn.mc = SLIM_MSG_MC_NEXT_REMOVE_CHANNEL;
	port->ch.state = SLIM_CH_STATE_REMOVED;

	वापस slim_करो_transfer(sdev->ctrl, &txn);
पूर्ण

अटल पूर्णांक slim_get_prate_code(पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(slim_presence_rate_table); i++) अणु
		अगर (rate == slim_presence_rate_table[i])
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * slim_stream_prepare() - Prepare a SLIMbus Stream
 *
 * @rt: instance of slim stream runसमय to configure
 * @cfg: new configuration क्रम the stream
 *
 * This API will configure SLIMbus stream with config parameters from cfg.
 * वापस zero on success and error code on failure. From ASoC DPCM framework,
 * this state is linked to hw_params() operation.
 */
पूर्णांक slim_stream_prepare(काष्ठा slim_stream_runसमय *rt,
			काष्ठा slim_stream_config *cfg)
अणु
	काष्ठा slim_controller *ctrl = rt->dev->ctrl;
	काष्ठा slim_port *port;
	पूर्णांक num_ports, i, port_id;

	अगर (rt->ports) अणु
		dev_err(&rt->dev->dev, "Stream already Prepared\n");
		वापस -EINVAL;
	पूर्ण

	num_ports = hweight32(cfg->port_mask);
	rt->ports = kसुस्मृति(num_ports, माप(*port), GFP_KERNEL);
	अगर (!rt->ports)
		वापस -ENOMEM;

	rt->num_ports = num_ports;
	rt->rate = cfg->rate;
	rt->bps = cfg->bps;
	rt->direction = cfg->direction;

	अगर (cfg->rate % ctrl->a_framer->superfreq) अणु
		/*
		 * data rate not exactly multiple of super frame,
		 * use PUSH/PULL protocol
		 */
		अगर (cfg->direction == SNDRV_PCM_STREAM_PLAYBACK)
			rt->prot = SLIM_PROTO_PUSH;
		अन्यथा
			rt->prot = SLIM_PROTO_PULL;
	पूर्ण अन्यथा अणु
		rt->prot = SLIM_PROTO_ISO;
	पूर्ण

	rt->ratem = cfg->rate/ctrl->a_framer->superfreq;

	i = 0;
	क्रम_each_set_bit(port_id, &cfg->port_mask, SLIM_DEVICE_MAX_PORTS) अणु
		port = &rt->ports[i];
		port->state = SLIM_PORT_DISCONNECTED;
		port->id = port_id;
		port->ch.prrate = slim_get_prate_code(cfg->rate);
		port->ch.id = cfg->chs[i];
		port->ch.data_fmt = SLIM_CH_DATA_FMT_NOT_DEFINED;
		port->ch.aux_fmt = SLIM_CH_AUX_FMT_NOT_APPLICABLE;
		port->ch.state = SLIM_CH_STATE_ALLOCATED;

		अगर (cfg->direction == SNDRV_PCM_STREAM_PLAYBACK)
			port->direction = SLIM_PORT_SINK;
		अन्यथा
			port->direction = SLIM_PORT_SOURCE;

		slim_connect_port_channel(rt, port);
		i++;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(slim_stream_prepare);

अटल पूर्णांक slim_define_channel_content(काष्ठा slim_stream_runसमय *stream,
				       काष्ठा slim_port *port)
अणु
	काष्ठा slim_device *sdev = stream->dev;
	u8 wbuf[4];
	काष्ठा slim_val_inf msg = अणु0, 4, शून्य, wbuf, शून्यपूर्ण;
	u8 mc = SLIM_MSG_MC_NEXT_DEFINE_CONTENT;
	DEFINE_SLIM_LDEST_TXN(txn, mc, 8, stream->dev->laddr, &msg);

	wbuf[0] = port->ch.id;
	wbuf[1] = port->ch.prrate;

	/* Frequency Locked क्रम ISO Protocol */
	अगर (stream->prot != SLIM_PROTO_ISO)
		wbuf[1] |= SLIM_CHANNEL_CONTENT_FL;

	wbuf[2] = port->ch.data_fmt | (port->ch.aux_fmt << 4);
	wbuf[3] = stream->bps/SLIM_SLOT_LEN_BITS;
	port->ch.state = SLIM_CH_STATE_CONTENT_DEFINED;

	वापस slim_करो_transfer(sdev->ctrl, &txn);
पूर्ण

अटल पूर्णांक slim_get_segdist_code(पूर्णांक ratem)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(segdist_codes); i++) अणु
		अगर (segdist_codes[i].ratem == ratem)
			वापस segdist_codes[i].segdist_code;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक slim_define_channel(काष्ठा slim_stream_runसमय *stream,
				       काष्ठा slim_port *port)
अणु
	काष्ठा slim_device *sdev = stream->dev;
	u8 wbuf[4];
	काष्ठा slim_val_inf msg = अणु0, 4, शून्य, wbuf, शून्यपूर्ण;
	u8 mc = SLIM_MSG_MC_NEXT_DEFINE_CHANNEL;
	DEFINE_SLIM_LDEST_TXN(txn, mc, 8, stream->dev->laddr, &msg);

	port->ch.seg_dist = slim_get_segdist_code(stream->ratem);

	wbuf[0] = port->ch.id;
	wbuf[1] = port->ch.seg_dist & 0xFF;
	wbuf[2] = (stream->prot << 4) | ((port->ch.seg_dist & 0xF00) >> 8);
	अगर (stream->prot == SLIM_PROTO_ISO)
		wbuf[3] = stream->bps/SLIM_SLOT_LEN_BITS;
	अन्यथा
		wbuf[3] = stream->bps/SLIM_SLOT_LEN_BITS + 1;

	port->ch.state = SLIM_CH_STATE_DEFINED;

	वापस slim_करो_transfer(sdev->ctrl, &txn);
पूर्ण

अटल पूर्णांक slim_activate_channel(काष्ठा slim_stream_runसमय *stream,
				 काष्ठा slim_port *port)
अणु
	काष्ठा slim_device *sdev = stream->dev;
	u8 wbuf[1];
	काष्ठा slim_val_inf msg = अणु0, 1, शून्य, wbuf, शून्यपूर्ण;
	u8 mc = SLIM_MSG_MC_NEXT_ACTIVATE_CHANNEL;
	DEFINE_SLIM_LDEST_TXN(txn, mc, 5, stream->dev->laddr, &msg);

	txn.msg->num_bytes = 1;
	txn.msg->wbuf = wbuf;
	wbuf[0] = port->ch.id;
	port->ch.state = SLIM_CH_STATE_ACTIVE;

	वापस slim_करो_transfer(sdev->ctrl, &txn);
पूर्ण

/**
 * slim_stream_enable() - Enable a prepared SLIMbus Stream
 *
 * @stream: instance of slim stream runसमय to enable
 *
 * This API will enable all the ports and channels associated with
 * SLIMbus stream
 *
 * Return: zero on success and error code on failure. From ASoC DPCM framework,
 * this state is linked to trigger() start operation.
 */
पूर्णांक slim_stream_enable(काष्ठा slim_stream_runसमय *stream)
अणु
	DEFINE_SLIM_BCAST_TXN(txn, SLIM_MSG_MC_BEGIN_RECONFIGURATION,
				3, SLIM_LA_MANAGER, शून्य);
	काष्ठा slim_controller *ctrl = stream->dev->ctrl;
	पूर्णांक ret, i;

	अगर (ctrl->enable_stream) अणु
		ret = ctrl->enable_stream(stream);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < stream->num_ports; i++)
			stream->ports[i].ch.state = SLIM_CH_STATE_ACTIVE;

		वापस ret;
	पूर्ण

	ret = slim_करो_transfer(ctrl, &txn);
	अगर (ret)
		वापस ret;

	/* define channels first beक्रमe activating them */
	क्रम (i = 0; i < stream->num_ports; i++) अणु
		काष्ठा slim_port *port = &stream->ports[i];

		slim_define_channel(stream, port);
		slim_define_channel_content(stream, port);
	पूर्ण

	क्रम (i = 0; i < stream->num_ports; i++) अणु
		काष्ठा slim_port *port = &stream->ports[i];

		slim_activate_channel(stream, port);
		port->state = SLIM_PORT_CONFIGURED;
	पूर्ण
	txn.mc = SLIM_MSG_MC_RECONFIGURE_NOW;

	वापस slim_करो_transfer(ctrl, &txn);
पूर्ण
EXPORT_SYMBOL_GPL(slim_stream_enable);

/**
 * slim_stream_disable() - Disable a SLIMbus Stream
 *
 * @stream: instance of slim stream runसमय to disable
 *
 * This API will disable all the ports and channels associated with
 * SLIMbus stream
 *
 * Return: zero on success and error code on failure. From ASoC DPCM framework,
 * this state is linked to trigger() छोड़ो operation.
 */
पूर्णांक slim_stream_disable(काष्ठा slim_stream_runसमय *stream)
अणु
	DEFINE_SLIM_BCAST_TXN(txn, SLIM_MSG_MC_BEGIN_RECONFIGURATION,
				3, SLIM_LA_MANAGER, शून्य);
	काष्ठा slim_controller *ctrl = stream->dev->ctrl;
	पूर्णांक ret, i;

	अगर (ctrl->disable_stream)
		ctrl->disable_stream(stream);

	ret = slim_करो_transfer(ctrl, &txn);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < stream->num_ports; i++)
		slim_deactivate_हटाओ_channel(stream, &stream->ports[i]);

	txn.mc = SLIM_MSG_MC_RECONFIGURE_NOW;

	वापस slim_करो_transfer(ctrl, &txn);
पूर्ण
EXPORT_SYMBOL_GPL(slim_stream_disable);

/**
 * slim_stream_unprepare() - Un-prepare a SLIMbus Stream
 *
 * @stream: instance of slim stream runसमय to unprepare
 *
 * This API will un allocate all the ports and channels associated with
 * SLIMbus stream
 *
 * Return: zero on success and error code on failure. From ASoC DPCM framework,
 * this state is linked to trigger() stop operation.
 */
पूर्णांक slim_stream_unprepare(काष्ठा slim_stream_runसमय *stream)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < stream->num_ports; i++)
		slim_disconnect_port(stream, &stream->ports[i]);

	kमुक्त(stream->ports);
	stream->ports = शून्य;
	stream->num_ports = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(slim_stream_unprepare);

/**
 * slim_stream_मुक्त() - Free a SLIMbus Stream
 *
 * @stream: instance of slim stream runसमय to मुक्त
 *
 * This API will un allocate all the memory associated with
 * slim stream runसमय, user is not allowed to make an dereference
 * to stream after this call.
 *
 * Return: zero on success and error code on failure. From ASoC DPCM framework,
 * this state is linked to shutकरोwn() operation.
 */
पूर्णांक slim_stream_मुक्त(काष्ठा slim_stream_runसमय *stream)
अणु
	काष्ठा slim_device *sdev = stream->dev;

	spin_lock(&sdev->stream_list_lock);
	list_del(&stream->node);
	spin_unlock(&sdev->stream_list_lock);

	kमुक्त(stream->name);
	kमुक्त(stream);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(slim_stream_मुक्त);
