<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCMCIA high-level CIS access functions
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * Copyright (C) 1999	     David A. Hinds
 * Copyright (C) 2004-2010   Dominik Broकरोwski
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>

#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/ds.h>
#समावेश "cs_internal.h"


/**
 * pccard_पढ़ो_tuple() - पूर्णांकernal CIS tuple access
 * @s:		the काष्ठा pcmcia_socket where the card is inserted
 * @function:	the device function we loop क्रम
 * @code:	which CIS code shall we look क्रम?
 * @parse:	buffer where the tuple shall be parsed (or शून्य, अगर no parse)
 *
 * pccard_पढ़ो_tuple() पढ़ोs out one tuple and attempts to parse it
 */
पूर्णांक pccard_पढ़ो_tuple(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक function,
		cisdata_t code, व्योम *parse)
अणु
	tuple_t tuple;
	cisdata_t *buf;
	पूर्णांक ret;

	buf = kदो_स्मृति(256, GFP_KERNEL);
	अगर (buf == शून्य) अणु
		dev_warn(&s->dev, "no memory to read tuple\n");
		वापस -ENOMEM;
	पूर्ण
	tuple.DesiredTuple = code;
	tuple.Attributes = 0;
	अगर (function == BIND_FN_ALL)
		tuple.Attributes = TUPLE_RETURN_COMMON;
	ret = pccard_get_first_tuple(s, function, &tuple);
	अगर (ret != 0)
		जाओ करोne;
	tuple.TupleData = buf;
	tuple.TupleOffset = 0;
	tuple.TupleDataMax = 255;
	ret = pccard_get_tuple_data(s, &tuple);
	अगर (ret != 0)
		जाओ करोne;
	ret = pcmcia_parse_tuple(&tuple, parse);
करोne:
	kमुक्त(buf);
	वापस ret;
पूर्ण


/**
 * pccard_loop_tuple() - loop over tuples in the CIS
 * @s:		the काष्ठा pcmcia_socket where the card is inserted
 * @function:	the device function we loop क्रम
 * @code:	which CIS code shall we look क्रम?
 * @parse:	buffer where the tuple shall be parsed (or शून्य, अगर no parse)
 * @priv_data:	निजी data to be passed to the loop_tuple function.
 * @loop_tuple:	function to call क्रम each CIS entry of type @function. IT
 *		माला_लो passed the raw tuple, the paresed tuple (अगर @parse is
 *		set) and @priv_data.
 *
 * pccard_loop_tuple() loops over all CIS entries of type @function, and
 * calls the @loop_tuple function क्रम each entry. If the call to @loop_tuple
 * वापसs 0, the loop निकासs. Returns 0 on success or errorcode otherwise.
 */
अटल पूर्णांक pccard_loop_tuple(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक function,
			     cisdata_t code, cisparse_t *parse, व्योम *priv_data,
			     पूर्णांक (*loop_tuple) (tuple_t *tuple,
					 cisparse_t *parse,
					 व्योम *priv_data))
अणु
	tuple_t tuple;
	cisdata_t *buf;
	पूर्णांक ret;

	buf = kzalloc(256, GFP_KERNEL);
	अगर (buf == शून्य) अणु
		dev_warn(&s->dev, "no memory to read tuple\n");
		वापस -ENOMEM;
	पूर्ण

	tuple.TupleData = buf;
	tuple.TupleDataMax = 255;
	tuple.TupleOffset = 0;
	tuple.DesiredTuple = code;
	tuple.Attributes = 0;

	ret = pccard_get_first_tuple(s, function, &tuple);
	जबतक (!ret) अणु
		अगर (pccard_get_tuple_data(s, &tuple))
			जाओ next_entry;

		अगर (parse)
			अगर (pcmcia_parse_tuple(&tuple, parse))
				जाओ next_entry;

		ret = loop_tuple(&tuple, parse, priv_data);
		अगर (!ret)
			अवरोध;

next_entry:
		ret = pccard_get_next_tuple(s, function, &tuple);
	पूर्ण

	kमुक्त(buf);
	वापस ret;
पूर्ण


/*
 * pcmcia_io_cfg_data_width() - convert cfgtable to data path width parameter
 */
अटल पूर्णांक pcmcia_io_cfg_data_width(अचिन्हित पूर्णांक flags)
अणु
	अगर (!(flags & CISTPL_IO_8BIT))
		वापस IO_DATA_PATH_WIDTH_16;
	अगर (!(flags & CISTPL_IO_16BIT))
		वापस IO_DATA_PATH_WIDTH_8;
	वापस IO_DATA_PATH_WIDTH_AUTO;
पूर्ण


काष्ठा pcmcia_cfg_mem अणु
	काष्ठा pcmcia_device *p_dev;
	पूर्णांक (*conf_check) (काष्ठा pcmcia_device *p_dev, व्योम *priv_data);
	व्योम *priv_data;
	cisparse_t parse;
	cistpl_cftable_entry_t dflt;
पूर्ण;

/*
 * pcmcia_करो_loop_config() - पूर्णांकernal helper क्रम pcmcia_loop_config()
 *
 * pcmcia_करो_loop_config() is the पूर्णांकernal callback क्रम the call from
 * pcmcia_loop_config() to pccard_loop_tuple(). Data is transferred
 * by a काष्ठा pcmcia_cfg_mem.
 */
अटल पूर्णांक pcmcia_करो_loop_config(tuple_t *tuple, cisparse_t *parse, व्योम *priv)
अणु
	काष्ठा pcmcia_cfg_mem *cfg_mem = priv;
	काष्ठा pcmcia_device *p_dev = cfg_mem->p_dev;
	cistpl_cftable_entry_t *cfg = &parse->cftable_entry;
	cistpl_cftable_entry_t *dflt = &cfg_mem->dflt;
	अचिन्हित पूर्णांक flags = p_dev->config_flags;
	अचिन्हित पूर्णांक vcc = p_dev->socket->socket.Vcc;

	dev_dbg(&p_dev->dev, "testing configuration %x, autoconf %x\n",
		cfg->index, flags);

	/* शेष values */
	cfg_mem->p_dev->config_index = cfg->index;
	अगर (cfg->flags & CISTPL_CFTABLE_DEFAULT)
		cfg_mem->dflt = *cfg;

	/* check क्रम matching Vcc? */
	अगर (flags & CONF_AUTO_CHECK_VCC) अणु
		अगर (cfg->vcc.present & (1 << CISTPL_POWER_VNOM)) अणु
			अगर (vcc != cfg->vcc.param[CISTPL_POWER_VNOM] / 10000)
				वापस -ENODEV;
		पूर्ण अन्यथा अगर (dflt->vcc.present & (1 << CISTPL_POWER_VNOM)) अणु
			अगर (vcc != dflt->vcc.param[CISTPL_POWER_VNOM] / 10000)
				वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* set Vpp? */
	अगर (flags & CONF_AUTO_SET_VPP) अणु
		अगर (cfg->vpp1.present & (1 << CISTPL_POWER_VNOM))
			p_dev->vpp = cfg->vpp1.param[CISTPL_POWER_VNOM] / 10000;
		अन्यथा अगर (dflt->vpp1.present & (1 << CISTPL_POWER_VNOM))
			p_dev->vpp =
				dflt->vpp1.param[CISTPL_POWER_VNOM] / 10000;
	पूर्ण

	/* enable audio? */
	अगर ((flags & CONF_AUTO_AUDIO) && (cfg->flags & CISTPL_CFTABLE_AUDIO))
		p_dev->config_flags |= CONF_ENABLE_SPKR;


	/* IO winकरोw settings? */
	अगर (flags & CONF_AUTO_SET_IO) अणु
		cistpl_io_t *io = (cfg->io.nwin) ? &cfg->io : &dflt->io;
		पूर्णांक i = 0;

		p_dev->resource[0]->start = p_dev->resource[0]->end = 0;
		p_dev->resource[1]->start = p_dev->resource[1]->end = 0;
		अगर (io->nwin == 0)
			वापस -ENODEV;

		p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
		p_dev->resource[0]->flags |=
					pcmcia_io_cfg_data_width(io->flags);
		अगर (io->nwin > 1) अणु
			/* For multअगरunction cards, by convention, we
			 * configure the network function with winकरोw 0,
			 * and serial with winकरोw 1 */
			i = (io->win[1].len > io->win[0].len);
			p_dev->resource[1]->flags = p_dev->resource[0]->flags;
			p_dev->resource[1]->start = io->win[1-i].base;
			p_dev->resource[1]->end = io->win[1-i].len;
		पूर्ण
		p_dev->resource[0]->start = io->win[i].base;
		p_dev->resource[0]->end = io->win[i].len;
		p_dev->io_lines = io->flags & CISTPL_IO_LINES_MASK;
	पूर्ण

	/* MEM winकरोw settings? */
	अगर (flags & CONF_AUTO_SET_IOMEM) अणु
		/* so far, we only set one memory winकरोw */
		cistpl_mem_t *mem = (cfg->mem.nwin) ? &cfg->mem : &dflt->mem;

		p_dev->resource[2]->start = p_dev->resource[2]->end = 0;
		अगर (mem->nwin == 0)
			वापस -ENODEV;

		p_dev->resource[2]->start = mem->win[0].host_addr;
		p_dev->resource[2]->end = mem->win[0].len;
		अगर (p_dev->resource[2]->end < 0x1000)
			p_dev->resource[2]->end = 0x1000;
		p_dev->card_addr = mem->win[0].card_addr;
	पूर्ण

	dev_dbg(&p_dev->dev,
		"checking configuration %x: %pr %pr %pr (%d lines)\n",
		p_dev->config_index, p_dev->resource[0], p_dev->resource[1],
		p_dev->resource[2], p_dev->io_lines);

	वापस cfg_mem->conf_check(p_dev, cfg_mem->priv_data);
पूर्ण

/**
 * pcmcia_loop_config() - loop over configuration options
 * @p_dev:	the काष्ठा pcmcia_device which we need to loop क्रम.
 * @conf_check:	function to call क्रम each configuration option.
 *		It माला_लो passed the काष्ठा pcmcia_device and निजी data
 *		being passed to pcmcia_loop_config()
 * @priv_data:	निजी data to be passed to the conf_check function.
 *
 * pcmcia_loop_config() loops over all configuration options, and calls
 * the driver-specअगरic conf_check() क्रम each one, checking whether
 * it is a valid one. Returns 0 on success or errorcode otherwise.
 */
पूर्णांक pcmcia_loop_config(काष्ठा pcmcia_device *p_dev,
		       पूर्णांक	(*conf_check)	(काष्ठा pcmcia_device *p_dev,
						 व्योम *priv_data),
		       व्योम *priv_data)
अणु
	काष्ठा pcmcia_cfg_mem *cfg_mem;
	पूर्णांक ret;

	cfg_mem = kzalloc(माप(काष्ठा pcmcia_cfg_mem), GFP_KERNEL);
	अगर (cfg_mem == शून्य)
		वापस -ENOMEM;

	cfg_mem->p_dev = p_dev;
	cfg_mem->conf_check = conf_check;
	cfg_mem->priv_data = priv_data;

	ret = pccard_loop_tuple(p_dev->socket, p_dev->func,
				CISTPL_CFTABLE_ENTRY, &cfg_mem->parse,
				cfg_mem, pcmcia_करो_loop_config);

	kमुक्त(cfg_mem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pcmcia_loop_config);


काष्ठा pcmcia_loop_mem अणु
	काष्ठा pcmcia_device *p_dev;
	व्योम *priv_data;
	पूर्णांक (*loop_tuple) (काष्ठा pcmcia_device *p_dev,
			   tuple_t *tuple,
			   व्योम *priv_data);
पूर्ण;

/*
 * pcmcia_करो_loop_tuple() - पूर्णांकernal helper क्रम pcmcia_loop_config()
 *
 * pcmcia_करो_loop_tuple() is the पूर्णांकernal callback क्रम the call from
 * pcmcia_loop_tuple() to pccard_loop_tuple(). Data is transferred
 * by a काष्ठा pcmcia_cfg_mem.
 */
अटल पूर्णांक pcmcia_करो_loop_tuple(tuple_t *tuple, cisparse_t *parse, व्योम *priv)
अणु
	काष्ठा pcmcia_loop_mem *loop = priv;

	वापस loop->loop_tuple(loop->p_dev, tuple, loop->priv_data);
पूर्ण;

/**
 * pcmcia_loop_tuple() - loop over tuples in the CIS
 * @p_dev:	the काष्ठा pcmcia_device which we need to loop क्रम.
 * @code:	which CIS code shall we look क्रम?
 * @priv_data:	निजी data to be passed to the loop_tuple function.
 * @loop_tuple:	function to call क्रम each CIS entry of type @function. IT
 *		माला_लो passed the raw tuple and @priv_data.
 *
 * pcmcia_loop_tuple() loops over all CIS entries of type @function, and
 * calls the @loop_tuple function क्रम each entry. If the call to @loop_tuple
 * वापसs 0, the loop निकासs. Returns 0 on success or errorcode otherwise.
 */
पूर्णांक pcmcia_loop_tuple(काष्ठा pcmcia_device *p_dev, cisdata_t code,
		      पूर्णांक (*loop_tuple) (काष्ठा pcmcia_device *p_dev,
					 tuple_t *tuple,
					 व्योम *priv_data),
		      व्योम *priv_data)
अणु
	काष्ठा pcmcia_loop_mem loop = अणु
		.p_dev = p_dev,
		.loop_tuple = loop_tuple,
		.priv_data = priv_dataपूर्ण;

	वापस pccard_loop_tuple(p_dev->socket, p_dev->func, code, शून्य,
				 &loop, pcmcia_करो_loop_tuple);
पूर्ण
EXPORT_SYMBOL(pcmcia_loop_tuple);


काष्ठा pcmcia_loop_get अणु
	माप_प्रकार len;
	cisdata_t **buf;
पूर्ण;

/*
 * pcmcia_करो_get_tuple() - पूर्णांकernal helper क्रम pcmcia_get_tuple()
 *
 * pcmcia_करो_get_tuple() is the पूर्णांकernal callback क्रम the call from
 * pcmcia_get_tuple() to pcmcia_loop_tuple(). As we're only पूर्णांकerested in
 * the first tuple, वापस 0 unconditionally. Create a memory buffer large
 * enough to hold the content of the tuple, and fill it with the tuple data.
 * The caller is responsible to मुक्त the buffer.
 */
अटल पूर्णांक pcmcia_करो_get_tuple(काष्ठा pcmcia_device *p_dev, tuple_t *tuple,
			       व्योम *priv)
अणु
	काष्ठा pcmcia_loop_get *get = priv;

	*get->buf = kzalloc(tuple->TupleDataLen, GFP_KERNEL);
	अगर (*get->buf) अणु
		get->len = tuple->TupleDataLen;
		स_नकल(*get->buf, tuple->TupleData, tuple->TupleDataLen);
	पूर्ण अन्यथा
		dev_dbg(&p_dev->dev, "do_get_tuple: out of memory\n");
	वापस 0;
पूर्ण

/**
 * pcmcia_get_tuple() - get first tuple from CIS
 * @p_dev:	the काष्ठा pcmcia_device which we need to loop क्रम.
 * @code:	which CIS code shall we look क्रम?
 * @buf:        poपूर्णांकer to store the buffer to.
 *
 * pcmcia_get_tuple() माला_लो the content of the first CIS entry of type @code.
 * It वापसs the buffer length (or zero). The caller is responsible to मुक्त
 * the buffer passed in @buf.
 */
माप_प्रकार pcmcia_get_tuple(काष्ठा pcmcia_device *p_dev, cisdata_t code,
			अचिन्हित अक्षर **buf)
अणु
	काष्ठा pcmcia_loop_get get = अणु
		.len = 0,
		.buf = buf,
	पूर्ण;

	*get.buf = शून्य;
	pcmcia_loop_tuple(p_dev, code, pcmcia_करो_get_tuple, &get);

	वापस get.len;
पूर्ण
EXPORT_SYMBOL(pcmcia_get_tuple);


/*
 * pcmcia_करो_get_mac() - पूर्णांकernal helper क्रम pcmcia_get_mac_from_cis()
 *
 * pcmcia_करो_get_mac() is the पूर्णांकernal callback क्रम the call from
 * pcmcia_get_mac_from_cis() to pcmcia_loop_tuple(). We check whether the
 * tuple contains a proper LAN_NODE_ID of length 6, and copy the data
 * to काष्ठा net_device->dev_addr[i].
 */
अटल पूर्णांक pcmcia_करो_get_mac(काष्ठा pcmcia_device *p_dev, tuple_t *tuple,
			     व्योम *priv)
अणु
	काष्ठा net_device *dev = priv;
	पूर्णांक i;

	अगर (tuple->TupleData[0] != CISTPL_FUNCE_LAN_NODE_ID)
		वापस -EINVAL;
	अगर (tuple->TupleDataLen < ETH_ALEN + 2) अणु
		dev_warn(&p_dev->dev, "Invalid CIS tuple length for "
			"LAN_NODE_ID\n");
		वापस -EINVAL;
	पूर्ण

	अगर (tuple->TupleData[1] != ETH_ALEN) अणु
		dev_warn(&p_dev->dev, "Invalid header for LAN_NODE_ID\n");
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = tuple->TupleData[i+2];
	वापस 0;
पूर्ण

/**
 * pcmcia_get_mac_from_cis() - पढ़ो out MAC address from CISTPL_FUNCE
 * @p_dev:	the काष्ठा pcmcia_device क्रम which we want the address.
 * @dev:	a properly prepared काष्ठा net_device to store the info to.
 *
 * pcmcia_get_mac_from_cis() पढ़ोs out the hardware MAC address from
 * CISTPL_FUNCE and stores it पूर्णांकo काष्ठा net_device *dev->dev_addr which
 * must be set up properly by the driver (see examples!).
 */
पूर्णांक pcmcia_get_mac_from_cis(काष्ठा pcmcia_device *p_dev, काष्ठा net_device *dev)
अणु
	वापस pcmcia_loop_tuple(p_dev, CISTPL_FUNCE, pcmcia_करो_get_mac, dev);
पूर्ण
EXPORT_SYMBOL(pcmcia_get_mac_from_cis);

