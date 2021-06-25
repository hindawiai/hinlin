<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Universal Interface क्रम Intel High Definition Audio Codec
 *
 * Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/core.h>
#समावेश <sound/hda_codec.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/tlv.h>
#समावेश <sound/initval.h>
#समावेश <sound/jack.h>
#समावेश "hda_local.h"
#समावेश "hda_beep.h"
#समावेश "hda_jack.h"
#समावेश <sound/hda_hwdep.h>
#समावेश <sound/hda_component.h>

#घोषणा codec_in_pm(codec)		snd_hdac_is_in_pm(&codec->core)
#घोषणा hda_codec_is_घातer_on(codec)	snd_hdac_is_घातer_on(&codec->core)
#घोषणा codec_has_epss(codec) \
	((codec)->core.घातer_caps & AC_PWRST_EPSS)
#घोषणा codec_has_clkstop(codec) \
	((codec)->core.घातer_caps & AC_PWRST_CLKSTOP)

/*
 * Send and receive a verb - passed to exec_verb override क्रम hdac_device
 */
अटल पूर्णांक codec_exec_verb(काष्ठा hdac_device *dev, अचिन्हित पूर्णांक cmd,
			   अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक *res)
अणु
	काष्ठा hda_codec *codec = container_of(dev, काष्ठा hda_codec, core);
	काष्ठा hda_bus *bus = codec->bus;
	पूर्णांक err;

	अगर (cmd == ~0)
		वापस -1;

 again:
	snd_hda_घातer_up_pm(codec);
	mutex_lock(&bus->core.cmd_mutex);
	अगर (flags & HDA_RW_NO_RESPONSE_FALLBACK)
		bus->no_response_fallback = 1;
	err = snd_hdac_bus_exec_verb_unlocked(&bus->core, codec->core.addr,
					      cmd, res);
	bus->no_response_fallback = 0;
	mutex_unlock(&bus->core.cmd_mutex);
	snd_hda_घातer_करोwn_pm(codec);
	अगर (!codec_in_pm(codec) && res && err == -EAGAIN) अणु
		अगर (bus->response_reset) अणु
			codec_dbg(codec,
				  "resetting BUS due to fatal communication error\n");
			snd_hda_bus_reset(bus);
		पूर्ण
		जाओ again;
	पूर्ण
	/* clear reset-flag when the communication माला_लो recovered */
	अगर (!err || codec_in_pm(codec))
		bus->response_reset = 0;
	वापस err;
पूर्ण

/**
 * snd_hda_sequence_ग_लिखो - sequence ग_लिखोs
 * @codec: the HDA codec
 * @seq: VERB array to send
 *
 * Send the commands sequentially from the given array.
 * The array must be terminated with NID=0.
 */
व्योम snd_hda_sequence_ग_लिखो(काष्ठा hda_codec *codec, स्थिर काष्ठा hda_verb *seq)
अणु
	क्रम (; seq->nid; seq++)
		snd_hda_codec_ग_लिखो(codec, seq->nid, 0, seq->verb, seq->param);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_sequence_ग_लिखो);

/* connection list element */
काष्ठा hda_conn_list अणु
	काष्ठा list_head list;
	पूर्णांक len;
	hda_nid_t nid;
	hda_nid_t conns[];
पूर्ण;

/* look up the cached results */
अटल काष्ठा hda_conn_list *
lookup_conn_list(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	काष्ठा hda_conn_list *p;
	list_क्रम_each_entry(p, &codec->conn_list, list) अणु
		अगर (p->nid == nid)
			वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक add_conn_list(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक len,
			 स्थिर hda_nid_t *list)
अणु
	काष्ठा hda_conn_list *p;

	p = kदो_स्मृति(काष्ठा_size(p, conns, len), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;
	p->len = len;
	p->nid = nid;
	स_नकल(p->conns, list, len * माप(hda_nid_t));
	list_add(&p->list, &codec->conn_list);
	वापस 0;
पूर्ण

अटल व्योम हटाओ_conn_list(काष्ठा hda_codec *codec)
अणु
	जबतक (!list_empty(&codec->conn_list)) अणु
		काष्ठा hda_conn_list *p;
		p = list_first_entry(&codec->conn_list, typeof(*p), list);
		list_del(&p->list);
		kमुक्त(p);
	पूर्ण
पूर्ण

/* पढ़ो the connection and add to the cache */
अटल पूर्णांक पढ़ो_and_add_raw_conns(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	hda_nid_t list[32];
	hda_nid_t *result = list;
	पूर्णांक len;

	len = snd_hda_get_raw_connections(codec, nid, list, ARRAY_SIZE(list));
	अगर (len == -ENOSPC) अणु
		len = snd_hda_get_num_raw_conns(codec, nid);
		result = kदो_स्मृति_array(len, माप(hda_nid_t), GFP_KERNEL);
		अगर (!result)
			वापस -ENOMEM;
		len = snd_hda_get_raw_connections(codec, nid, result, len);
	पूर्ण
	अगर (len >= 0)
		len = snd_hda_override_conn_list(codec, nid, len, result);
	अगर (result != list)
		kमुक्त(result);
	वापस len;
पूर्ण

/**
 * snd_hda_get_conn_list - get connection list
 * @codec: the HDA codec
 * @nid: NID to parse
 * @listp: the poपूर्णांकer to store NID list
 *
 * Parses the connection list of the given widget and stores the poपूर्णांकer
 * to the list of NIDs.
 *
 * Returns the number of connections, or a negative error code.
 *
 * Note that the वापसed poपूर्णांकer isn't रक्षित against the list
 * modअगरication.  If snd_hda_override_conn_list() might be called
 * concurrently, protect with a mutex appropriately.
 */
पूर्णांक snd_hda_get_conn_list(काष्ठा hda_codec *codec, hda_nid_t nid,
			  स्थिर hda_nid_t **listp)
अणु
	bool added = false;

	क्रम (;;) अणु
		पूर्णांक err;
		स्थिर काष्ठा hda_conn_list *p;

		/* अगर the connection-list is alपढ़ोy cached, पढ़ो it */
		p = lookup_conn_list(codec, nid);
		अगर (p) अणु
			अगर (listp)
				*listp = p->conns;
			वापस p->len;
		पूर्ण
		अगर (snd_BUG_ON(added))
			वापस -EINVAL;

		err = पढ़ो_and_add_raw_conns(codec, nid);
		अगर (err < 0)
			वापस err;
		added = true;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_conn_list);

/**
 * snd_hda_get_connections - copy connection list
 * @codec: the HDA codec
 * @nid: NID to parse
 * @conn_list: connection list array; when शून्य, checks only the size
 * @max_conns: max. number of connections to store
 *
 * Parses the connection list of the given widget and stores the list
 * of NIDs.
 *
 * Returns the number of connections, or a negative error code.
 */
पूर्णांक snd_hda_get_connections(काष्ठा hda_codec *codec, hda_nid_t nid,
			    hda_nid_t *conn_list, पूर्णांक max_conns)
अणु
	स्थिर hda_nid_t *list;
	पूर्णांक len = snd_hda_get_conn_list(codec, nid, &list);

	अगर (len > 0 && conn_list) अणु
		अगर (len > max_conns) अणु
			codec_err(codec, "Too many connections %d for NID 0x%x\n",
				   len, nid);
			वापस -EINVAL;
		पूर्ण
		स_नकल(conn_list, list, len * माप(hda_nid_t));
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_connections);

/**
 * snd_hda_override_conn_list - add/modअगरy the connection-list to cache
 * @codec: the HDA codec
 * @nid: NID to parse
 * @len: number of connection list entries
 * @list: the list of connection entries
 *
 * Add or modअगरy the given connection-list to the cache.  If the corresponding
 * cache alपढ़ोy exists, invalidate it and append a new one.
 *
 * Returns zero or a negative error code.
 */
पूर्णांक snd_hda_override_conn_list(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक len,
			       स्थिर hda_nid_t *list)
अणु
	काष्ठा hda_conn_list *p;

	p = lookup_conn_list(codec, nid);
	अगर (p) अणु
		list_del(&p->list);
		kमुक्त(p);
	पूर्ण

	वापस add_conn_list(codec, nid, len, list);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_override_conn_list);

/**
 * snd_hda_get_conn_index - get the connection index of the given NID
 * @codec: the HDA codec
 * @mux: NID containing the list
 * @nid: NID to select
 * @recursive: 1 when searching NID recursively, otherwise 0
 *
 * Parses the connection list of the widget @mux and checks whether the
 * widget @nid is present.  If it is, वापस the connection index.
 * Otherwise it वापसs -1.
 */
पूर्णांक snd_hda_get_conn_index(काष्ठा hda_codec *codec, hda_nid_t mux,
			   hda_nid_t nid, पूर्णांक recursive)
अणु
	स्थिर hda_nid_t *conn;
	पूर्णांक i, nums;

	nums = snd_hda_get_conn_list(codec, mux, &conn);
	क्रम (i = 0; i < nums; i++)
		अगर (conn[i] == nid)
			वापस i;
	अगर (!recursive)
		वापस -1;
	अगर (recursive > 10) अणु
		codec_dbg(codec, "too deep connection for 0x%x\n", nid);
		वापस -1;
	पूर्ण
	recursive++;
	क्रम (i = 0; i < nums; i++) अणु
		अचिन्हित पूर्णांक type = get_wcaps_type(get_wcaps(codec, conn[i]));
		अगर (type == AC_WID_PIN || type == AC_WID_AUD_OUT)
			जारी;
		अगर (snd_hda_get_conn_index(codec, conn[i], nid, recursive) >= 0)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_conn_index);

/**
 * snd_hda_get_num_devices - get DEVLIST_LEN parameter of the given widget
 *  @codec: the HDA codec
 *  @nid: NID of the pin to parse
 *
 * Get the device entry number on the given widget. This is a feature of
 * DP MST audio. Each pin can have several device entries in it.
 */
अचिन्हित पूर्णांक snd_hda_get_num_devices(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक wcaps = get_wcaps(codec, nid);
	अचिन्हित पूर्णांक parm;

	अगर (!codec->dp_mst || !(wcaps & AC_WCAP_DIGITAL) ||
	    get_wcaps_type(wcaps) != AC_WID_PIN)
		वापस 0;

	parm = snd_hdac_पढ़ो_parm_uncached(&codec->core, nid, AC_PAR_DEVLIST_LEN);
	अगर (parm == -1)
		parm = 0;
	वापस parm & AC_DEV_LIST_LEN_MASK;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_num_devices);

/**
 * snd_hda_get_devices - copy device list without cache
 * @codec: the HDA codec
 * @nid: NID of the pin to parse
 * @dev_list: device list array
 * @max_devices: max. number of devices to store
 *
 * Copy the device list. This info is dynamic and so not cached.
 * Currently called only from hda_proc.c, so not exported.
 */
पूर्णांक snd_hda_get_devices(काष्ठा hda_codec *codec, hda_nid_t nid,
			u8 *dev_list, पूर्णांक max_devices)
अणु
	अचिन्हित पूर्णांक parm;
	पूर्णांक i, dev_len, devices;

	parm = snd_hda_get_num_devices(codec, nid);
	अगर (!parm)	/* not multi-stream capable */
		वापस 0;

	dev_len = parm + 1;
	dev_len = dev_len < max_devices ? dev_len : max_devices;

	devices = 0;
	जबतक (devices < dev_len) अणु
		अगर (snd_hdac_पढ़ो(&codec->core, nid,
				  AC_VERB_GET_DEVICE_LIST, devices, &parm))
			अवरोध; /* error */

		क्रम (i = 0; i < 8; i++) अणु
			dev_list[devices] = (u8)parm;
			parm >>= 4;
			devices++;
			अगर (devices >= dev_len)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस devices;
पूर्ण

/**
 * snd_hda_get_dev_select - get device entry select on the pin
 * @codec: the HDA codec
 * @nid: NID of the pin to get device entry select
 *
 * Get the devcie entry select on the pin. Return the device entry
 * id selected on the pin. Return 0 means the first device entry
 * is selected or MST is not supported.
 */
पूर्णांक snd_hda_get_dev_select(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	/* not support dp_mst will always वापस 0, using first dev_entry */
	अगर (!codec->dp_mst)
		वापस 0;

	वापस snd_hda_codec_पढ़ो(codec, nid, 0, AC_VERB_GET_DEVICE_SEL, 0);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_dev_select);

/**
 * snd_hda_set_dev_select - set device entry select on the pin
 * @codec: the HDA codec
 * @nid: NID of the pin to set device entry select
 * @dev_id: device entry id to be set
 *
 * Set the device entry select on the pin nid.
 */
पूर्णांक snd_hda_set_dev_select(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dev_id)
अणु
	पूर्णांक ret, num_devices;

	/* not support dp_mst will always वापस 0, using first dev_entry */
	अगर (!codec->dp_mst)
		वापस 0;

	/* AC_PAR_DEVLIST_LEN is 0 based. */
	num_devices = snd_hda_get_num_devices(codec, nid) + 1;
	/* If Device List Length is 0 (num_device = 1),
	 * the pin is not multi stream capable.
	 * Do nothing in this हाल.
	 */
	अगर (num_devices == 1)
		वापस 0;

	/* Behavior of setting index being equal to or greater than
	 * Device List Length is not predictable
	 */
	अगर (num_devices <= dev_id)
		वापस -EINVAL;

	ret = snd_hda_codec_ग_लिखो(codec, nid, 0,
			AC_VERB_SET_DEVICE_SEL, dev_id);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_set_dev_select);

/*
 * पढ़ो widget caps क्रम each widget and store in cache
 */
अटल पूर्णांक पढ़ो_widget_caps(काष्ठा hda_codec *codec, hda_nid_t fg_node)
अणु
	पूर्णांक i;
	hda_nid_t nid;

	codec->wcaps = kदो_स्मृति_array(codec->core.num_nodes, 4, GFP_KERNEL);
	अगर (!codec->wcaps)
		वापस -ENOMEM;
	nid = codec->core.start_nid;
	क्रम (i = 0; i < codec->core.num_nodes; i++, nid++)
		codec->wcaps[i] = snd_hdac_पढ़ो_parm_uncached(&codec->core,
					nid, AC_PAR_AUDIO_WIDGET_CAP);
	वापस 0;
पूर्ण

/* पढ़ो all pin शेष configurations and save codec->init_pins */
अटल पूर्णांक पढ़ो_pin_शेषs(काष्ठा hda_codec *codec)
अणु
	hda_nid_t nid;

	क्रम_each_hda_codec_node(nid, codec) अणु
		काष्ठा hda_pincfg *pin;
		अचिन्हित पूर्णांक wcaps = get_wcaps(codec, nid);
		अचिन्हित पूर्णांक wid_type = get_wcaps_type(wcaps);
		अगर (wid_type != AC_WID_PIN)
			जारी;
		pin = snd_array_new(&codec->init_pins);
		अगर (!pin)
			वापस -ENOMEM;
		pin->nid = nid;
		pin->cfg = snd_hda_codec_पढ़ो(codec, nid, 0,
					      AC_VERB_GET_CONFIG_DEFAULT, 0);
		/*
		 * all device entries are the same widget control so far
		 * fixme: अगर any codec is dअगरferent, need fix here
		 */
		pin->ctrl = snd_hda_codec_पढ़ो(codec, nid, 0,
					       AC_VERB_GET_PIN_WIDGET_CONTROL,
					       0);
	पूर्ण
	वापस 0;
पूर्ण

/* look up the given pin config list and वापस the item matching with NID */
अटल काष्ठा hda_pincfg *look_up_pincfg(काष्ठा hda_codec *codec,
					 काष्ठा snd_array *array,
					 hda_nid_t nid)
अणु
	काष्ठा hda_pincfg *pin;
	पूर्णांक i;

	snd_array_क्रम_each(array, i, pin) अणु
		अगर (pin->nid == nid)
			वापस pin;
	पूर्ण
	वापस शून्य;
पूर्ण

/* set the current pin config value क्रम the given NID.
 * the value is cached, and पढ़ो via snd_hda_codec_get_pincfg()
 */
पूर्णांक snd_hda_add_pincfg(काष्ठा hda_codec *codec, काष्ठा snd_array *list,
		       hda_nid_t nid, अचिन्हित पूर्णांक cfg)
अणु
	काष्ठा hda_pincfg *pin;

	/* the check below may be invalid when pins are added by a fixup
	 * dynamically (e.g. via snd_hda_codec_update_widमाला_लो()), so disabled
	 * क्रम now
	 */
	/*
	अगर (get_wcaps_type(get_wcaps(codec, nid)) != AC_WID_PIN)
		वापस -EINVAL;
	*/

	pin = look_up_pincfg(codec, list, nid);
	अगर (!pin) अणु
		pin = snd_array_new(list);
		अगर (!pin)
			वापस -ENOMEM;
		pin->nid = nid;
	पूर्ण
	pin->cfg = cfg;
	वापस 0;
पूर्ण

/**
 * snd_hda_codec_set_pincfg - Override a pin शेष configuration
 * @codec: the HDA codec
 * @nid: NID to set the pin config
 * @cfg: the pin शेष config value
 *
 * Override a pin शेष configuration value in the cache.
 * This value can be पढ़ो by snd_hda_codec_get_pincfg() in a higher
 * priority than the real hardware value.
 */
पूर्णांक snd_hda_codec_set_pincfg(काष्ठा hda_codec *codec,
			     hda_nid_t nid, अचिन्हित पूर्णांक cfg)
अणु
	वापस snd_hda_add_pincfg(codec, &codec->driver_pins, nid, cfg);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_set_pincfg);

/**
 * snd_hda_codec_get_pincfg - Obtain a pin-शेष configuration
 * @codec: the HDA codec
 * @nid: NID to get the pin config
 *
 * Get the current pin config value of the given pin NID.
 * If the pincfg value is cached or overridden via sysfs or driver,
 * वापसs the cached value.
 */
अचिन्हित पूर्णांक snd_hda_codec_get_pincfg(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	काष्ठा hda_pincfg *pin;

#अगर_घोषित CONFIG_SND_HDA_RECONFIG
	अणु
		अचिन्हित पूर्णांक cfg = 0;
		mutex_lock(&codec->user_mutex);
		pin = look_up_pincfg(codec, &codec->user_pins, nid);
		अगर (pin)
			cfg = pin->cfg;
		mutex_unlock(&codec->user_mutex);
		अगर (cfg)
			वापस cfg;
	पूर्ण
#पूर्ण_अगर
	pin = look_up_pincfg(codec, &codec->driver_pins, nid);
	अगर (pin)
		वापस pin->cfg;
	pin = look_up_pincfg(codec, &codec->init_pins, nid);
	अगर (pin)
		वापस pin->cfg;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_get_pincfg);

/**
 * snd_hda_codec_set_pin_target - remember the current pinctl target value
 * @codec: the HDA codec
 * @nid: pin NID
 * @val: asचिन्हित pinctl value
 *
 * This function stores the given value to a pinctl target value in the
 * pincfg table.  This isn't always as same as the actually written value
 * but can be referred at any समय via snd_hda_codec_get_pin_target().
 */
पूर्णांक snd_hda_codec_set_pin_target(काष्ठा hda_codec *codec, hda_nid_t nid,
				 अचिन्हित पूर्णांक val)
अणु
	काष्ठा hda_pincfg *pin;

	pin = look_up_pincfg(codec, &codec->init_pins, nid);
	अगर (!pin)
		वापस -EINVAL;
	pin->target = val;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_set_pin_target);

/**
 * snd_hda_codec_get_pin_target - वापस the current pinctl target value
 * @codec: the HDA codec
 * @nid: pin NID
 */
पूर्णांक snd_hda_codec_get_pin_target(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	काष्ठा hda_pincfg *pin;

	pin = look_up_pincfg(codec, &codec->init_pins, nid);
	अगर (!pin)
		वापस 0;
	वापस pin->target;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_get_pin_target);

/**
 * snd_hda_shutup_pins - Shut up all pins
 * @codec: the HDA codec
 *
 * Clear all pin controls to shup up beक्रमe suspend क्रम aव्योमing click noise.
 * The controls aren't cached so that they can be resumed properly.
 */
व्योम snd_hda_shutup_pins(काष्ठा hda_codec *codec)
अणु
	स्थिर काष्ठा hda_pincfg *pin;
	पूर्णांक i;

	/* करोn't shut up pins when unloading the driver; otherwise it अवरोधs
	 * the शेष pin setup at the next load of the driver
	 */
	अगर (codec->bus->shutकरोwn)
		वापस;
	snd_array_क्रम_each(&codec->init_pins, i, pin) अणु
		/* use पढ़ो here क्रम syncing after issuing each verb */
		snd_hda_codec_पढ़ो(codec, pin->nid, 0,
				   AC_VERB_SET_PIN_WIDGET_CONTROL, 0);
	पूर्ण
	codec->pins_shutup = 1;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_shutup_pins);

#अगर_घोषित CONFIG_PM
/* Restore the pin controls cleared previously via snd_hda_shutup_pins() */
अटल व्योम restore_shutup_pins(काष्ठा hda_codec *codec)
अणु
	स्थिर काष्ठा hda_pincfg *pin;
	पूर्णांक i;

	अगर (!codec->pins_shutup)
		वापस;
	अगर (codec->bus->shutकरोwn)
		वापस;
	snd_array_क्रम_each(&codec->init_pins, i, pin) अणु
		snd_hda_codec_ग_लिखो(codec, pin->nid, 0,
				    AC_VERB_SET_PIN_WIDGET_CONTROL,
				    pin->ctrl);
	पूर्ण
	codec->pins_shutup = 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम hda_jackpoll_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hda_codec *codec =
		container_of(work, काष्ठा hda_codec, jackpoll_work.work);

	/* क्रम non-polling trigger: we need nothing अगर alपढ़ोy घातered on */
	अगर (!codec->jackpoll_पूर्णांकerval && snd_hdac_is_घातer_on(&codec->core))
		वापस;

	/* the घातer-up/करोwn sequence triggers the runसमय resume */
	snd_hda_घातer_up_pm(codec);
	/* update jacks manually अगर polling is required, too */
	अगर (codec->jackpoll_पूर्णांकerval) अणु
		snd_hda_jack_set_dirty_all(codec);
		snd_hda_jack_poll_all(codec);
	पूर्ण
	snd_hda_घातer_करोwn_pm(codec);

	अगर (!codec->jackpoll_पूर्णांकerval)
		वापस;

	schedule_delayed_work(&codec->jackpoll_work,
			      codec->jackpoll_पूर्णांकerval);
पूर्ण

/* release all pincfg lists */
अटल व्योम मुक्त_init_pincfgs(काष्ठा hda_codec *codec)
अणु
	snd_array_मुक्त(&codec->driver_pins);
#अगर_घोषित CONFIG_SND_HDA_RECONFIG
	snd_array_मुक्त(&codec->user_pins);
#पूर्ण_अगर
	snd_array_मुक्त(&codec->init_pins);
पूर्ण

/*
 * audio-converter setup caches
 */
काष्ठा hda_cvt_setup अणु
	hda_nid_t nid;
	u8 stream_tag;
	u8 channel_id;
	u16 क्रमmat_id;
	अचिन्हित अक्षर active;	/* cvt is currently used */
	अचिन्हित अक्षर dirty;	/* setups should be cleared */
पूर्ण;

/* get or create a cache entry क्रम the given audio converter NID */
अटल काष्ठा hda_cvt_setup *
get_hda_cvt_setup(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	काष्ठा hda_cvt_setup *p;
	पूर्णांक i;

	snd_array_क्रम_each(&codec->cvt_setups, i, p) अणु
		अगर (p->nid == nid)
			वापस p;
	पूर्ण
	p = snd_array_new(&codec->cvt_setups);
	अगर (p)
		p->nid = nid;
	वापस p;
पूर्ण

/*
 * PCM device
 */
अटल व्योम release_pcm(काष्ठा kref *kref)
अणु
	काष्ठा hda_pcm *pcm = container_of(kref, काष्ठा hda_pcm, kref);

	अगर (pcm->pcm)
		snd_device_मुक्त(pcm->codec->card, pcm->pcm);
	clear_bit(pcm->device, pcm->codec->bus->pcm_dev_bits);
	kमुक्त(pcm->name);
	kमुक्त(pcm);
पूर्ण

व्योम snd_hda_codec_pcm_put(काष्ठा hda_pcm *pcm)
अणु
	kref_put(&pcm->kref, release_pcm);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_pcm_put);

काष्ठा hda_pcm *snd_hda_codec_pcm_new(काष्ठा hda_codec *codec,
				      स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा hda_pcm *pcm;
	बहु_सूची args;

	pcm = kzalloc(माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस शून्य;

	pcm->codec = codec;
	kref_init(&pcm->kref);
	बहु_शुरू(args, fmt);
	pcm->name = kvaप्र_लिखो(GFP_KERNEL, fmt, args);
	बहु_पूर्ण(args);
	अगर (!pcm->name) अणु
		kमुक्त(pcm);
		वापस शून्य;
	पूर्ण

	list_add_tail(&pcm->list, &codec->pcm_list_head);
	वापस pcm;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_pcm_new);

/*
 * codec deकाष्ठाor
 */
अटल व्योम codec_release_pcms(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_pcm *pcm, *n;

	list_क्रम_each_entry_safe(pcm, n, &codec->pcm_list_head, list) अणु
		list_del_init(&pcm->list);
		अगर (pcm->pcm)
			snd_device_disconnect(codec->card, pcm->pcm);
		snd_hda_codec_pcm_put(pcm);
	पूर्ण
पूर्ण

व्योम snd_hda_codec_cleanup_क्रम_unbind(काष्ठा hda_codec *codec)
अणु
	अगर (codec->रेजिस्टरed) अणु
		/* pm_runसमय_put() is called in snd_hdac_device_निकास() */
		pm_runसमय_get_noresume(hda_codec_dev(codec));
		pm_runसमय_disable(hda_codec_dev(codec));
		codec->रेजिस्टरed = 0;
	पूर्ण

	cancel_delayed_work_sync(&codec->jackpoll_work);
	अगर (!codec->in_मुक्तing)
		snd_hda_ctls_clear(codec);
	codec_release_pcms(codec);
	snd_hda_detach_beep_device(codec);
	स_रखो(&codec->patch_ops, 0, माप(codec->patch_ops));
	snd_hda_jack_tbl_clear(codec);
	codec->proc_widget_hook = शून्य;
	codec->spec = शून्य;

	/* मुक्त only driver_pins so that init_pins + user_pins are restored */
	snd_array_मुक्त(&codec->driver_pins);
	snd_array_मुक्त(&codec->cvt_setups);
	snd_array_मुक्त(&codec->spdअगर_out);
	snd_array_मुक्त(&codec->verbs);
	codec->preset = शून्य;
	codec->follower_dig_outs = शून्य;
	codec->spdअगर_status_reset = 0;
	snd_array_मुक्त(&codec->mixers);
	snd_array_मुक्त(&codec->nids);
	हटाओ_conn_list(codec);
	snd_hdac_regmap_निकास(&codec->core);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_cleanup_क्रम_unbind);

अटल अचिन्हित पूर्णांक hda_set_घातer_state(काष्ठा hda_codec *codec,
				अचिन्हित पूर्णांक घातer_state);

/* enable/disable display घातer per codec */
अटल व्योम codec_display_घातer(काष्ठा hda_codec *codec, bool enable)
अणु
	अगर (codec->display_घातer_control)
		snd_hdac_display_घातer(&codec->bus->core, codec->addr, enable);
पूर्ण

/* also called from hda_bind.c */
व्योम snd_hda_codec_रेजिस्टर(काष्ठा hda_codec *codec)
अणु
	अगर (codec->रेजिस्टरed)
		वापस;
	अगर (device_is_रेजिस्टरed(hda_codec_dev(codec))) अणु
		codec_display_घातer(codec, true);
		pm_runसमय_enable(hda_codec_dev(codec));
		/* it was घातered up in snd_hda_codec_new(), now all करोne */
		snd_hda_घातer_करोwn(codec);
		codec->रेजिस्टरed = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_hda_codec_dev_रेजिस्टर(काष्ठा snd_device *device)
अणु
	snd_hda_codec_रेजिस्टर(device->device_data);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hda_codec_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा hda_codec *codec = device->device_data;

	codec->in_मुक्तing = 1;
	/*
	 * snd_hda_codec_device_new() is used by legacy HDA and ASoC driver.
	 * We can't unरेजिस्टर ASoC device since it will be unरेजिस्टरed in
	 * snd_hdac_ext_bus_device_हटाओ().
	 */
	अगर (codec->core.type == HDA_DEV_LEGACY)
		snd_hdac_device_unरेजिस्टर(&codec->core);
	codec_display_घातer(codec, false);

	/*
	 * In the हाल of ASoC HD-audio bus, the device refcount is released in
	 * snd_hdac_ext_bus_device_हटाओ() explicitly.
	 */
	अगर (codec->core.type == HDA_DEV_LEGACY)
		put_device(hda_codec_dev(codec));

	वापस 0;
पूर्ण

अटल व्योम snd_hda_codec_dev_release(काष्ठा device *dev)
अणु
	काष्ठा hda_codec *codec = dev_to_hda_codec(dev);

	मुक्त_init_pincfgs(codec);
	snd_hdac_device_निकास(&codec->core);
	snd_hda_sysfs_clear(codec);
	kमुक्त(codec->modelname);
	kमुक्त(codec->wcaps);

	/*
	 * In the हाल of ASoC HD-audio, hda_codec is device managed.
	 * It will be मुक्तd when the ASoC device is हटाओd.
	 */
	अगर (codec->core.type == HDA_DEV_LEGACY)
		kमुक्त(codec);
पूर्ण

#घोषणा DEV_NAME_LEN 31

अटल पूर्णांक snd_hda_codec_device_init(काष्ठा hda_bus *bus, काष्ठा snd_card *card,
			अचिन्हित पूर्णांक codec_addr, काष्ठा hda_codec **codecp)
अणु
	अक्षर name[DEV_NAME_LEN];
	काष्ठा hda_codec *codec;
	पूर्णांक err;

	dev_dbg(card->dev, "%s: entry\n", __func__);

	अगर (snd_BUG_ON(!bus))
		वापस -EINVAL;
	अगर (snd_BUG_ON(codec_addr > HDA_MAX_CODEC_ADDRESS))
		वापस -EINVAL;

	codec = kzalloc(माप(*codec), GFP_KERNEL);
	अगर (!codec)
		वापस -ENOMEM;

	प्र_लिखो(name, "hdaudioC%dD%d", card->number, codec_addr);
	err = snd_hdac_device_init(&codec->core, &bus->core, name, codec_addr);
	अगर (err < 0) अणु
		kमुक्त(codec);
		वापस err;
	पूर्ण

	codec->core.type = HDA_DEV_LEGACY;
	*codecp = codec;

	वापस err;
पूर्ण

/**
 * snd_hda_codec_new - create a HDA codec
 * @bus: the bus to assign
 * @card: card क्रम this codec
 * @codec_addr: the codec address
 * @codecp: the poपूर्णांकer to store the generated codec
 *
 * Returns 0 अगर successful, or a negative error code.
 */
पूर्णांक snd_hda_codec_new(काष्ठा hda_bus *bus, काष्ठा snd_card *card,
		      अचिन्हित पूर्णांक codec_addr, काष्ठा hda_codec **codecp)
अणु
	पूर्णांक ret;

	ret = snd_hda_codec_device_init(bus, card, codec_addr, codecp);
	अगर (ret < 0)
		वापस ret;

	वापस snd_hda_codec_device_new(bus, card, codec_addr, *codecp);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_new);

पूर्णांक snd_hda_codec_device_new(काष्ठा hda_bus *bus, काष्ठा snd_card *card,
			अचिन्हित पूर्णांक codec_addr, काष्ठा hda_codec *codec)
अणु
	अक्षर component[31];
	hda_nid_t fg;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops dev_ops = अणु
		.dev_रेजिस्टर = snd_hda_codec_dev_रेजिस्टर,
		.dev_मुक्त = snd_hda_codec_dev_मुक्त,
	पूर्ण;

	dev_dbg(card->dev, "%s: entry\n", __func__);

	अगर (snd_BUG_ON(!bus))
		वापस -EINVAL;
	अगर (snd_BUG_ON(codec_addr > HDA_MAX_CODEC_ADDRESS))
		वापस -EINVAL;

	codec->core.dev.release = snd_hda_codec_dev_release;
	codec->core.exec_verb = codec_exec_verb;

	codec->bus = bus;
	codec->card = card;
	codec->addr = codec_addr;
	mutex_init(&codec->spdअगर_mutex);
	mutex_init(&codec->control_mutex);
	snd_array_init(&codec->mixers, माप(काष्ठा hda_nid_item), 32);
	snd_array_init(&codec->nids, माप(काष्ठा hda_nid_item), 32);
	snd_array_init(&codec->init_pins, माप(काष्ठा hda_pincfg), 16);
	snd_array_init(&codec->driver_pins, माप(काष्ठा hda_pincfg), 16);
	snd_array_init(&codec->cvt_setups, माप(काष्ठा hda_cvt_setup), 8);
	snd_array_init(&codec->spdअगर_out, माप(काष्ठा hda_spdअगर_out), 16);
	snd_array_init(&codec->jacktbl, माप(काष्ठा hda_jack_tbl), 16);
	snd_array_init(&codec->verbs, माप(काष्ठा hda_verb *), 8);
	INIT_LIST_HEAD(&codec->conn_list);
	INIT_LIST_HEAD(&codec->pcm_list_head);

	INIT_DELAYED_WORK(&codec->jackpoll_work, hda_jackpoll_work);
	codec->depop_delay = -1;
	codec->fixup_id = HDA_FIXUP_ID_NOT_SET;

#अगर_घोषित CONFIG_PM
	codec->घातer_jअगरfies = jअगरfies;
#पूर्ण_अगर

	snd_hda_sysfs_init(codec);

	अगर (codec->bus->modelname) अणु
		codec->modelname = kstrdup(codec->bus->modelname, GFP_KERNEL);
		अगर (!codec->modelname) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण
	पूर्ण

	fg = codec->core.afg ? codec->core.afg : codec->core.mfg;
	err = पढ़ो_widget_caps(codec, fg);
	अगर (err < 0)
		जाओ error;
	err = पढ़ो_pin_शेषs(codec);
	अगर (err < 0)
		जाओ error;

	/* घातer-up all beक्रमe initialization */
	hda_set_घातer_state(codec, AC_PWRST_D0);
	codec->core.dev.घातer.घातer_state = PMSG_ON;

	snd_hda_codec_proc_new(codec);

	snd_hda_create_hwdep(codec);

	प्र_लिखो(component, "HDA:%08x,%08x,%08x", codec->core.venकरोr_id,
		codec->core.subप्रणाली_id, codec->core.revision_id);
	snd_component_add(card, component);

	err = snd_device_new(card, SNDRV_DEV_CODEC, codec, &dev_ops);
	अगर (err < 0)
		जाओ error;

	/* PM runसमय needs to be enabled later after binding codec */
	pm_runसमय_क्रमbid(&codec->core.dev);

	वापस 0;

 error:
	put_device(hda_codec_dev(codec));
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_device_new);

/**
 * snd_hda_codec_update_widमाला_लो - Refresh widget caps and pin शेषs
 * @codec: the HDA codec
 *
 * Forcibly refresh the all widget caps and the init pin configurations of
 * the given codec.
 */
पूर्णांक snd_hda_codec_update_widमाला_लो(काष्ठा hda_codec *codec)
अणु
	hda_nid_t fg;
	पूर्णांक err;

	err = snd_hdac_refresh_widमाला_लो(&codec->core);
	अगर (err < 0)
		वापस err;

	/* Assume the function group node करोes not change,
	 * only the widget nodes may change.
	 */
	kमुक्त(codec->wcaps);
	fg = codec->core.afg ? codec->core.afg : codec->core.mfg;
	err = पढ़ो_widget_caps(codec, fg);
	अगर (err < 0)
		वापस err;

	snd_array_मुक्त(&codec->init_pins);
	err = पढ़ो_pin_शेषs(codec);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_update_widमाला_लो);

/* update the stream-id अगर changed */
अटल व्योम update_pcm_stream_id(काष्ठा hda_codec *codec,
				 काष्ठा hda_cvt_setup *p, hda_nid_t nid,
				 u32 stream_tag, पूर्णांक channel_id)
अणु
	अचिन्हित पूर्णांक oldval, newval;

	अगर (p->stream_tag != stream_tag || p->channel_id != channel_id) अणु
		oldval = snd_hda_codec_पढ़ो(codec, nid, 0, AC_VERB_GET_CONV, 0);
		newval = (stream_tag << 4) | channel_id;
		अगर (oldval != newval)
			snd_hda_codec_ग_लिखो(codec, nid, 0,
					    AC_VERB_SET_CHANNEL_STREAMID,
					    newval);
		p->stream_tag = stream_tag;
		p->channel_id = channel_id;
	पूर्ण
पूर्ण

/* update the क्रमmat-id अगर changed */
अटल व्योम update_pcm_क्रमmat(काष्ठा hda_codec *codec, काष्ठा hda_cvt_setup *p,
			      hda_nid_t nid, पूर्णांक क्रमmat)
अणु
	अचिन्हित पूर्णांक oldval;

	अगर (p->क्रमmat_id != क्रमmat) अणु
		oldval = snd_hda_codec_पढ़ो(codec, nid, 0,
					    AC_VERB_GET_STREAM_FORMAT, 0);
		अगर (oldval != क्रमmat) अणु
			msleep(1);
			snd_hda_codec_ग_लिखो(codec, nid, 0,
					    AC_VERB_SET_STREAM_FORMAT,
					    क्रमmat);
		पूर्ण
		p->क्रमmat_id = क्रमmat;
	पूर्ण
पूर्ण

/**
 * snd_hda_codec_setup_stream - set up the codec क्रम streaming
 * @codec: the CODEC to set up
 * @nid: the NID to set up
 * @stream_tag: stream tag to pass, it's between 0x1 and 0xf.
 * @channel_id: channel id to pass, zero based.
 * @क्रमmat: stream क्रमmat.
 */
व्योम snd_hda_codec_setup_stream(काष्ठा hda_codec *codec, hda_nid_t nid,
				u32 stream_tag,
				पूर्णांक channel_id, पूर्णांक क्रमmat)
अणु
	काष्ठा hda_codec *c;
	काष्ठा hda_cvt_setup *p;
	पूर्णांक type;
	पूर्णांक i;

	अगर (!nid)
		वापस;

	codec_dbg(codec,
		  "hda_codec_setup_stream: NID=0x%x, stream=0x%x, channel=%d, format=0x%x\n",
		  nid, stream_tag, channel_id, क्रमmat);
	p = get_hda_cvt_setup(codec, nid);
	अगर (!p)
		वापस;

	अगर (codec->patch_ops.stream_pm)
		codec->patch_ops.stream_pm(codec, nid, true);
	अगर (codec->pcm_क्रमmat_first)
		update_pcm_क्रमmat(codec, p, nid, क्रमmat);
	update_pcm_stream_id(codec, p, nid, stream_tag, channel_id);
	अगर (!codec->pcm_क्रमmat_first)
		update_pcm_क्रमmat(codec, p, nid, क्रमmat);

	p->active = 1;
	p->dirty = 0;

	/* make other inactive cvts with the same stream-tag dirty */
	type = get_wcaps_type(get_wcaps(codec, nid));
	list_क्रम_each_codec(c, codec->bus) अणु
		snd_array_क्रम_each(&c->cvt_setups, i, p) अणु
			अगर (!p->active && p->stream_tag == stream_tag &&
			    get_wcaps_type(get_wcaps(c, p->nid)) == type)
				p->dirty = 1;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_setup_stream);

अटल व्योम really_cleanup_stream(काष्ठा hda_codec *codec,
				  काष्ठा hda_cvt_setup *q);

/**
 * __snd_hda_codec_cleanup_stream - clean up the codec क्रम closing
 * @codec: the CODEC to clean up
 * @nid: the NID to clean up
 * @करो_now: really clean up the stream instead of clearing the active flag
 */
व्योम __snd_hda_codec_cleanup_stream(काष्ठा hda_codec *codec, hda_nid_t nid,
				    पूर्णांक करो_now)
अणु
	काष्ठा hda_cvt_setup *p;

	अगर (!nid)
		वापस;

	अगर (codec->no_sticky_stream)
		करो_now = 1;

	codec_dbg(codec, "hda_codec_cleanup_stream: NID=0x%x\n", nid);
	p = get_hda_cvt_setup(codec, nid);
	अगर (p) अणु
		/* here we just clear the active flag when करो_now isn't set;
		 * actual clean-ups will be करोne later in
		 * purअगरy_inactive_streams() called from snd_hda_codec_prpapre()
		 */
		अगर (करो_now)
			really_cleanup_stream(codec, p);
		अन्यथा
			p->active = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__snd_hda_codec_cleanup_stream);

अटल व्योम really_cleanup_stream(काष्ठा hda_codec *codec,
				  काष्ठा hda_cvt_setup *q)
अणु
	hda_nid_t nid = q->nid;
	अगर (q->stream_tag || q->channel_id)
		snd_hda_codec_ग_लिखो(codec, nid, 0, AC_VERB_SET_CHANNEL_STREAMID, 0);
	अगर (q->क्रमmat_id)
		snd_hda_codec_ग_लिखो(codec, nid, 0, AC_VERB_SET_STREAM_FORMAT, 0
);
	स_रखो(q, 0, माप(*q));
	q->nid = nid;
	अगर (codec->patch_ops.stream_pm)
		codec->patch_ops.stream_pm(codec, nid, false);
पूर्ण

/* clean up the all conflicting obsolete streams */
अटल व्योम purअगरy_inactive_streams(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_codec *c;
	काष्ठा hda_cvt_setup *p;
	पूर्णांक i;

	list_क्रम_each_codec(c, codec->bus) अणु
		snd_array_क्रम_each(&c->cvt_setups, i, p) अणु
			अगर (p->dirty)
				really_cleanup_stream(c, p);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
/* clean up all streams; called from suspend */
अटल व्योम hda_cleanup_all_streams(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_cvt_setup *p;
	पूर्णांक i;

	snd_array_क्रम_each(&codec->cvt_setups, i, p) अणु
		अगर (p->stream_tag)
			really_cleanup_stream(codec, p);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * amp access functions
 */

/**
 * query_amp_caps - query AMP capabilities
 * @codec: the HD-auio codec
 * @nid: the NID to query
 * @direction: either #HDA_INPUT or #HDA_OUTPUT
 *
 * Query AMP capabilities क्रम the given widget and direction.
 * Returns the obtained capability bits.
 *
 * When cap bits have been alपढ़ोy पढ़ो, this करोesn't पढ़ो again but
 * वापसs the cached value.
 */
u32 query_amp_caps(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक direction)
अणु
	अगर (!(get_wcaps(codec, nid) & AC_WCAP_AMP_OVRD))
		nid = codec->core.afg;
	वापस snd_hda_param_पढ़ो(codec, nid,
				  direction == HDA_OUTPUT ?
				  AC_PAR_AMP_OUT_CAP : AC_PAR_AMP_IN_CAP);
पूर्ण
EXPORT_SYMBOL_GPL(query_amp_caps);

/**
 * snd_hda_check_amp_caps - query AMP capabilities
 * @codec: the HD-audio codec
 * @nid: the NID to query
 * @dir: either #HDA_INPUT or #HDA_OUTPUT
 * @bits: bit mask to check the result
 *
 * Check whether the widget has the given amp capability क्रम the direction.
 */
bool snd_hda_check_amp_caps(काष्ठा hda_codec *codec, hda_nid_t nid,
			   पूर्णांक dir, अचिन्हित पूर्णांक bits)
अणु
	अगर (!nid)
		वापस false;
	अगर (get_wcaps(codec, nid) & (1 << (dir + 1)))
		अगर (query_amp_caps(codec, nid, dir) & bits)
			वापस true;
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_check_amp_caps);

/**
 * snd_hda_override_amp_caps - Override the AMP capabilities
 * @codec: the CODEC to clean up
 * @nid: the NID to clean up
 * @dir: either #HDA_INPUT or #HDA_OUTPUT
 * @caps: the capability bits to set
 *
 * Override the cached AMP caps bits value by the given one.
 * This function is useful अगर the driver needs to adjust the AMP ranges,
 * e.g. limit to 0dB, etc.
 *
 * Returns zero अगर successful or a negative error code.
 */
पूर्णांक snd_hda_override_amp_caps(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dir,
			      अचिन्हित पूर्णांक caps)
अणु
	अचिन्हित पूर्णांक parm;

	snd_hda_override_wcaps(codec, nid,
			       get_wcaps(codec, nid) | AC_WCAP_AMP_OVRD);
	parm = dir == HDA_OUTPUT ? AC_PAR_AMP_OUT_CAP : AC_PAR_AMP_IN_CAP;
	वापस snd_hdac_override_parm(&codec->core, nid, parm, caps);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_override_amp_caps);

अटल अचिन्हित पूर्णांक encode_amp(काष्ठा hda_codec *codec, hda_nid_t nid,
			       पूर्णांक ch, पूर्णांक dir, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक cmd = snd_hdac_regmap_encode_amp(nid, ch, dir, idx);

	/* enable fake mute अगर no h/w mute but min=mute */
	अगर ((query_amp_caps(codec, nid, dir) &
	     (AC_AMPCAP_MUTE | AC_AMPCAP_MIN_MUTE)) == AC_AMPCAP_MIN_MUTE)
		cmd |= AC_AMP_FAKE_MUTE;
	वापस cmd;
पूर्ण

/**
 * snd_hda_codec_amp_update - update the AMP mono value
 * @codec: HD-audio codec
 * @nid: NID to पढ़ो the AMP value
 * @ch: channel to update (0 or 1)
 * @dir: #HDA_INPUT or #HDA_OUTPUT
 * @idx: the index value (only क्रम input direction)
 * @mask: bit mask to set
 * @val: the bits value to set
 *
 * Update the AMP values क्रम the given channel, direction and index.
 */
पूर्णांक snd_hda_codec_amp_update(काष्ठा hda_codec *codec, hda_nid_t nid,
			     पूर्णांक ch, पूर्णांक dir, पूर्णांक idx, पूर्णांक mask, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक cmd = encode_amp(codec, nid, ch, dir, idx);

	वापस snd_hdac_regmap_update_raw(&codec->core, cmd, mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_amp_update);

/**
 * snd_hda_codec_amp_stereo - update the AMP stereo values
 * @codec: HD-audio codec
 * @nid: NID to पढ़ो the AMP value
 * @direction: #HDA_INPUT or #HDA_OUTPUT
 * @idx: the index value (only क्रम input direction)
 * @mask: bit mask to set
 * @val: the bits value to set
 *
 * Update the AMP values like snd_hda_codec_amp_update(), but क्रम a
 * stereo widget with the same mask and value.
 */
पूर्णांक snd_hda_codec_amp_stereo(काष्ठा hda_codec *codec, hda_nid_t nid,
			     पूर्णांक direction, पूर्णांक idx, पूर्णांक mask, पूर्णांक val)
अणु
	पूर्णांक ch, ret = 0;

	अगर (snd_BUG_ON(mask & ~0xff))
		mask &= 0xff;
	क्रम (ch = 0; ch < 2; ch++)
		ret |= snd_hda_codec_amp_update(codec, nid, ch, direction,
						idx, mask, val);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_amp_stereo);

/**
 * snd_hda_codec_amp_init - initialize the AMP value
 * @codec: the HDA codec
 * @nid: NID to पढ़ो the AMP value
 * @ch: channel (left=0 or right=1)
 * @dir: #HDA_INPUT or #HDA_OUTPUT
 * @idx: the index value (only क्रम input direction)
 * @mask: bit mask to set
 * @val: the bits value to set
 *
 * Works like snd_hda_codec_amp_update() but it ग_लिखोs the value only at
 * the first access.  If the amp was alपढ़ोy initialized / updated beक्रमehand,
 * this करोes nothing.
 */
पूर्णांक snd_hda_codec_amp_init(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक ch,
			   पूर्णांक dir, पूर्णांक idx, पूर्णांक mask, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक cmd = encode_amp(codec, nid, ch, dir, idx);

	अगर (!codec->core.regmap)
		वापस -EINVAL;
	वापस snd_hdac_regmap_update_raw_once(&codec->core, cmd, mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_amp_init);

/**
 * snd_hda_codec_amp_init_stereo - initialize the stereo AMP value
 * @codec: the HDA codec
 * @nid: NID to पढ़ो the AMP value
 * @dir: #HDA_INPUT or #HDA_OUTPUT
 * @idx: the index value (only क्रम input direction)
 * @mask: bit mask to set
 * @val: the bits value to set
 *
 * Call snd_hda_codec_amp_init() क्रम both stereo channels.
 */
पूर्णांक snd_hda_codec_amp_init_stereo(काष्ठा hda_codec *codec, hda_nid_t nid,
				  पूर्णांक dir, पूर्णांक idx, पूर्णांक mask, पूर्णांक val)
अणु
	पूर्णांक ch, ret = 0;

	अगर (snd_BUG_ON(mask & ~0xff))
		mask &= 0xff;
	क्रम (ch = 0; ch < 2; ch++)
		ret |= snd_hda_codec_amp_init(codec, nid, ch, dir,
					      idx, mask, val);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_amp_init_stereo);

अटल u32 get_amp_max_value(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dir,
			     अचिन्हित पूर्णांक ofs)
अणु
	u32 caps = query_amp_caps(codec, nid, dir);
	/* get num steps */
	caps = (caps & AC_AMPCAP_NUM_STEPS) >> AC_AMPCAP_NUM_STEPS_SHIFT;
	अगर (ofs < caps)
		caps -= ofs;
	वापस caps;
पूर्ण

/**
 * snd_hda_mixer_amp_volume_info - Info callback क्रम a standard AMP mixer
 * @kcontrol: referred ctl element
 * @uinfo: poपूर्णांकer to get/store the data
 *
 * The control element is supposed to have the निजी_value field
 * set up via HDA_COMPOSE_AMP_VAL*() or related macros.
 */
पूर्णांक snd_hda_mixer_amp_volume_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	u16 nid = get_amp_nid(kcontrol);
	u8 chs = get_amp_channels(kcontrol);
	पूर्णांक dir = get_amp_direction(kcontrol);
	अचिन्हित पूर्णांक ofs = get_amp_offset(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = chs == 3 ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = get_amp_max_value(codec, nid, dir, ofs);
	अगर (!uinfo->value.पूर्णांकeger.max) अणु
		codec_warn(codec,
			   "num_steps = 0 for NID=0x%x (ctl = %s)\n",
			   nid, kcontrol->id.name);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_mixer_amp_volume_info);


अटल अंतरभूत अचिन्हित पूर्णांक
पढ़ो_amp_value(काष्ठा hda_codec *codec, hda_nid_t nid,
	       पूर्णांक ch, पूर्णांक dir, पूर्णांक idx, अचिन्हित पूर्णांक ofs)
अणु
	अचिन्हित पूर्णांक val;
	val = snd_hda_codec_amp_पढ़ो(codec, nid, ch, dir, idx);
	val &= HDA_AMP_VOLMASK;
	अगर (val >= ofs)
		val -= ofs;
	अन्यथा
		val = 0;
	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक
update_amp_value(काष्ठा hda_codec *codec, hda_nid_t nid,
		 पूर्णांक ch, पूर्णांक dir, पूर्णांक idx, अचिन्हित पूर्णांक ofs,
		 अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक maxval;

	अगर (val > 0)
		val += ofs;
	/* ofs = 0: raw max value */
	maxval = get_amp_max_value(codec, nid, dir, 0);
	अगर (val > maxval)
		val = maxval;
	वापस snd_hda_codec_amp_update(codec, nid, ch, dir, idx,
					HDA_AMP_VOLMASK, val);
पूर्ण

/**
 * snd_hda_mixer_amp_volume_get - Get callback क्रम a standard AMP mixer volume
 * @kcontrol: ctl element
 * @ucontrol: poपूर्णांकer to get/store the data
 *
 * The control element is supposed to have the निजी_value field
 * set up via HDA_COMPOSE_AMP_VAL*() or related macros.
 */
पूर्णांक snd_hda_mixer_amp_volume_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक chs = get_amp_channels(kcontrol);
	पूर्णांक dir = get_amp_direction(kcontrol);
	पूर्णांक idx = get_amp_index(kcontrol);
	अचिन्हित पूर्णांक ofs = get_amp_offset(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;

	अगर (chs & 1)
		*valp++ = पढ़ो_amp_value(codec, nid, 0, dir, idx, ofs);
	अगर (chs & 2)
		*valp = पढ़ो_amp_value(codec, nid, 1, dir, idx, ofs);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_mixer_amp_volume_get);

/**
 * snd_hda_mixer_amp_volume_put - Put callback क्रम a standard AMP mixer volume
 * @kcontrol: ctl element
 * @ucontrol: poपूर्णांकer to get/store the data
 *
 * The control element is supposed to have the निजी_value field
 * set up via HDA_COMPOSE_AMP_VAL*() or related macros.
 */
पूर्णांक snd_hda_mixer_amp_volume_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक chs = get_amp_channels(kcontrol);
	पूर्णांक dir = get_amp_direction(kcontrol);
	पूर्णांक idx = get_amp_index(kcontrol);
	अचिन्हित पूर्णांक ofs = get_amp_offset(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	पूर्णांक change = 0;

	अगर (chs & 1) अणु
		change = update_amp_value(codec, nid, 0, dir, idx, ofs, *valp);
		valp++;
	पूर्ण
	अगर (chs & 2)
		change |= update_amp_value(codec, nid, 1, dir, idx, ofs, *valp);
	वापस change;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_mixer_amp_volume_put);

/* inquiry the amp caps and convert to TLV */
अटल व्योम get_ctl_amp_tlv(काष्ठा snd_kcontrol *kcontrol, अचिन्हित पूर्णांक *tlv)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक dir = get_amp_direction(kcontrol);
	अचिन्हित पूर्णांक ofs = get_amp_offset(kcontrol);
	bool min_mute = get_amp_min_mute(kcontrol);
	u32 caps, val1, val2;

	caps = query_amp_caps(codec, nid, dir);
	val2 = (caps & AC_AMPCAP_STEP_SIZE) >> AC_AMPCAP_STEP_SIZE_SHIFT;
	val2 = (val2 + 1) * 25;
	val1 = -((caps & AC_AMPCAP_OFFSET) >> AC_AMPCAP_OFFSET_SHIFT);
	val1 += ofs;
	val1 = ((पूर्णांक)val1) * ((पूर्णांक)val2);
	अगर (min_mute || (caps & AC_AMPCAP_MIN_MUTE))
		val2 |= TLV_DB_SCALE_MUTE;
	tlv[SNDRV_CTL_TLVO_TYPE] = SNDRV_CTL_TLVT_DB_SCALE;
	tlv[SNDRV_CTL_TLVO_LEN] = 2 * माप(अचिन्हित पूर्णांक);
	tlv[SNDRV_CTL_TLVO_DB_SCALE_MIN] = val1;
	tlv[SNDRV_CTL_TLVO_DB_SCALE_MUTE_AND_STEP] = val2;
पूर्ण

/**
 * snd_hda_mixer_amp_tlv - TLV callback क्रम a standard AMP mixer volume
 * @kcontrol: ctl element
 * @op_flag: operation flag
 * @size: byte size of input TLV
 * @_tlv: TLV data
 *
 * The control element is supposed to have the निजी_value field
 * set up via HDA_COMPOSE_AMP_VAL*() or related macros.
 */
पूर्णांक snd_hda_mixer_amp_tlv(काष्ठा snd_kcontrol *kcontrol, पूर्णांक op_flag,
			  अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक __user *_tlv)
अणु
	अचिन्हित पूर्णांक tlv[4];

	अगर (size < 4 * माप(अचिन्हित पूर्णांक))
		वापस -ENOMEM;
	get_ctl_amp_tlv(kcontrol, tlv);
	अगर (copy_to_user(_tlv, tlv, माप(tlv)))
		वापस -EFAULT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_mixer_amp_tlv);

/**
 * snd_hda_set_vmaster_tlv - Set TLV क्रम a भव master control
 * @codec: HD-audio codec
 * @nid: NID of a reference widget
 * @dir: #HDA_INPUT or #HDA_OUTPUT
 * @tlv: TLV data to be stored, at least 4 elements
 *
 * Set (अटल) TLV data क्रम a भव master volume using the AMP caps
 * obtained from the reference NID.
 * The volume range is recalculated as अगर the max volume is 0dB.
 */
व्योम snd_hda_set_vmaster_tlv(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dir,
			     अचिन्हित पूर्णांक *tlv)
अणु
	u32 caps;
	पूर्णांक nums, step;

	caps = query_amp_caps(codec, nid, dir);
	nums = (caps & AC_AMPCAP_NUM_STEPS) >> AC_AMPCAP_NUM_STEPS_SHIFT;
	step = (caps & AC_AMPCAP_STEP_SIZE) >> AC_AMPCAP_STEP_SIZE_SHIFT;
	step = (step + 1) * 25;
	tlv[SNDRV_CTL_TLVO_TYPE] = SNDRV_CTL_TLVT_DB_SCALE;
	tlv[SNDRV_CTL_TLVO_LEN] = 2 * माप(अचिन्हित पूर्णांक);
	tlv[SNDRV_CTL_TLVO_DB_SCALE_MIN] = -nums * step;
	tlv[SNDRV_CTL_TLVO_DB_SCALE_MUTE_AND_STEP] = step;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_set_vmaster_tlv);

/* find a mixer control element with the given name */
अटल काष्ठा snd_kcontrol *
find_mixer_ctl(काष्ठा hda_codec *codec, स्थिर अक्षर *name, पूर्णांक dev, पूर्णांक idx)
अणु
	काष्ठा snd_ctl_elem_id id;
	स_रखो(&id, 0, माप(id));
	id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	id.device = dev;
	id.index = idx;
	अगर (snd_BUG_ON(म_माप(name) >= माप(id.name)))
		वापस शून्य;
	म_नकल(id.name, name);
	वापस snd_ctl_find_id(codec->card, &id);
पूर्ण

/**
 * snd_hda_find_mixer_ctl - Find a mixer control element with the given name
 * @codec: HD-audio codec
 * @name: ctl id name string
 *
 * Get the control element with the given id string and IFACE_MIXER.
 */
काष्ठा snd_kcontrol *snd_hda_find_mixer_ctl(काष्ठा hda_codec *codec,
					    स्थिर अक्षर *name)
अणु
	वापस find_mixer_ctl(codec, name, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_find_mixer_ctl);

अटल पूर्णांक find_empty_mixer_ctl_idx(काष्ठा hda_codec *codec, स्थिर अक्षर *name,
				    पूर्णांक start_idx)
अणु
	पूर्णांक i, idx;
	/* 16 ctlrs should be large enough */
	क्रम (i = 0, idx = start_idx; i < 16; i++, idx++) अणु
		अगर (!find_mixer_ctl(codec, name, 0, idx))
			वापस idx;
	पूर्ण
	वापस -EBUSY;
पूर्ण

/**
 * snd_hda_ctl_add - Add a control element and assign to the codec
 * @codec: HD-audio codec
 * @nid: corresponding NID (optional)
 * @kctl: the control element to assign
 *
 * Add the given control element to an array inside the codec instance.
 * All control elements beदीर्घing to a codec are supposed to be added
 * by this function so that a proper clean-up works at the मुक्त or
 * reconfiguration समय.
 *
 * If non-zero @nid is passed, the NID is asचिन्हित to the control element.
 * The assignment is shown in the codec proc file.
 *
 * snd_hda_ctl_add() checks the control subdev id field whether
 * #HDA_SUBDEV_NID_FLAG bit is set.  If set (and @nid is zero), the lower
 * bits value is taken as the NID to assign. The #HDA_NID_ITEM_AMP bit
 * specअगरies अगर kctl->निजी_value is a HDA amplअगरier value.
 */
पूर्णांक snd_hda_ctl_add(काष्ठा hda_codec *codec, hda_nid_t nid,
		    काष्ठा snd_kcontrol *kctl)
अणु
	पूर्णांक err;
	अचिन्हित लघु flags = 0;
	काष्ठा hda_nid_item *item;

	अगर (kctl->id.subdevice & HDA_SUBDEV_AMP_FLAG) अणु
		flags |= HDA_NID_ITEM_AMP;
		अगर (nid == 0)
			nid = get_amp_nid_(kctl->निजी_value);
	पूर्ण
	अगर ((kctl->id.subdevice & HDA_SUBDEV_NID_FLAG) != 0 && nid == 0)
		nid = kctl->id.subdevice & 0xffff;
	अगर (kctl->id.subdevice & (HDA_SUBDEV_NID_FLAG|HDA_SUBDEV_AMP_FLAG))
		kctl->id.subdevice = 0;
	err = snd_ctl_add(codec->card, kctl);
	अगर (err < 0)
		वापस err;
	item = snd_array_new(&codec->mixers);
	अगर (!item)
		वापस -ENOMEM;
	item->kctl = kctl;
	item->nid = nid;
	item->flags = flags;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_ctl_add);

/**
 * snd_hda_add_nid - Assign a NID to a control element
 * @codec: HD-audio codec
 * @nid: corresponding NID (optional)
 * @kctl: the control element to assign
 * @index: index to kctl
 *
 * Add the given control element to an array inside the codec instance.
 * This function is used when #snd_hda_ctl_add cannot be used क्रम 1:1
 * NID:KCTL mapping - क्रम example "Capture Source" selector.
 */
पूर्णांक snd_hda_add_nid(काष्ठा hda_codec *codec, काष्ठा snd_kcontrol *kctl,
		    अचिन्हित पूर्णांक index, hda_nid_t nid)
अणु
	काष्ठा hda_nid_item *item;

	अगर (nid > 0) अणु
		item = snd_array_new(&codec->nids);
		अगर (!item)
			वापस -ENOMEM;
		item->kctl = kctl;
		item->index = index;
		item->nid = nid;
		वापस 0;
	पूर्ण
	codec_err(codec, "no NID for mapping control %s:%d:%d\n",
		  kctl->id.name, kctl->id.index, index);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_add_nid);

/**
 * snd_hda_ctls_clear - Clear all controls asचिन्हित to the given codec
 * @codec: HD-audio codec
 */
व्योम snd_hda_ctls_clear(काष्ठा hda_codec *codec)
अणु
	पूर्णांक i;
	काष्ठा hda_nid_item *items = codec->mixers.list;
	क्रम (i = 0; i < codec->mixers.used; i++)
		snd_ctl_हटाओ(codec->card, items[i].kctl);
	snd_array_मुक्त(&codec->mixers);
	snd_array_मुक्त(&codec->nids);
पूर्ण

/**
 * snd_hda_lock_devices - pseuकरो device locking
 * @bus: the BUS
 *
 * toggle card->shutकरोwn to allow/disallow the device access (as a hack)
 */
पूर्णांक snd_hda_lock_devices(काष्ठा hda_bus *bus)
अणु
	काष्ठा snd_card *card = bus->card;
	काष्ठा hda_codec *codec;

	spin_lock(&card->files_lock);
	अगर (card->shutकरोwn)
		जाओ err_unlock;
	card->shutकरोwn = 1;
	अगर (!list_empty(&card->ctl_files))
		जाओ err_clear;

	list_क्रम_each_codec(codec, bus) अणु
		काष्ठा hda_pcm *cpcm;
		list_क्रम_each_entry(cpcm, &codec->pcm_list_head, list) अणु
			अगर (!cpcm->pcm)
				जारी;
			अगर (cpcm->pcm->streams[0].substream_खोलोed ||
			    cpcm->pcm->streams[1].substream_खोलोed)
				जाओ err_clear;
		पूर्ण
	पूर्ण
	spin_unlock(&card->files_lock);
	वापस 0;

 err_clear:
	card->shutकरोwn = 0;
 err_unlock:
	spin_unlock(&card->files_lock);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_lock_devices);

/**
 * snd_hda_unlock_devices - pseuकरो device unlocking
 * @bus: the BUS
 */
व्योम snd_hda_unlock_devices(काष्ठा hda_bus *bus)
अणु
	काष्ठा snd_card *card = bus->card;

	spin_lock(&card->files_lock);
	card->shutकरोwn = 0;
	spin_unlock(&card->files_lock);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_unlock_devices);

/**
 * snd_hda_codec_reset - Clear all objects asचिन्हित to the codec
 * @codec: HD-audio codec
 *
 * This मुक्तs the all PCM and control elements asचिन्हित to the codec, and
 * clears the caches and restores the pin शेष configurations.
 *
 * When a device is being used, it वापसs -EBSY.  If successfully मुक्तd,
 * वापसs zero.
 */
पूर्णांक snd_hda_codec_reset(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_bus *bus = codec->bus;

	अगर (snd_hda_lock_devices(bus) < 0)
		वापस -EBUSY;

	/* OK, let it मुक्त */
	device_release_driver(hda_codec_dev(codec));

	/* allow device access again */
	snd_hda_unlock_devices(bus);
	वापस 0;
पूर्ण

प्रकार पूर्णांक (*map_follower_func_t)(काष्ठा hda_codec *, व्योम *, काष्ठा snd_kcontrol *);

/* apply the function to all matching follower ctls in the mixer list */
अटल पूर्णांक map_followers(काष्ठा hda_codec *codec, स्थिर अक्षर * स्थिर *followers,
			 स्थिर अक्षर *suffix, map_follower_func_t func, व्योम *data)
अणु
	काष्ठा hda_nid_item *items;
	स्थिर अक्षर * स्थिर *s;
	पूर्णांक i, err;

	items = codec->mixers.list;
	क्रम (i = 0; i < codec->mixers.used; i++) अणु
		काष्ठा snd_kcontrol *sctl = items[i].kctl;
		अगर (!sctl || sctl->id.अगरace != SNDRV_CTL_ELEM_IFACE_MIXER)
			जारी;
		क्रम (s = followers; *s; s++) अणु
			अक्षर क्षणिकe[माप(sctl->id.name)];
			स्थिर अक्षर *name = *s;
			अगर (suffix) अणु
				snम_लिखो(क्षणिकe, माप(क्षणिकe), "%s %s",
					 name, suffix);
				name = क्षणिकe;
			पूर्ण
			अगर (!म_भेद(sctl->id.name, name)) अणु
				err = func(codec, data, sctl);
				अगर (err)
					वापस err;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_follower_present(काष्ठा hda_codec *codec,
				  व्योम *data, काष्ठा snd_kcontrol *sctl)
अणु
	वापस 1;
पूर्ण

/* call kctl->put with the given value(s) */
अटल पूर्णांक put_kctl_with_value(काष्ठा snd_kcontrol *kctl, पूर्णांक val)
अणु
	काष्ठा snd_ctl_elem_value *ucontrol;
	ucontrol = kzalloc(माप(*ucontrol), GFP_KERNEL);
	अगर (!ucontrol)
		वापस -ENOMEM;
	ucontrol->value.पूर्णांकeger.value[0] = val;
	ucontrol->value.पूर्णांकeger.value[1] = val;
	kctl->put(kctl, ucontrol);
	kमुक्त(ucontrol);
	वापस 0;
पूर्ण

काष्ठा follower_init_arg अणु
	काष्ठा hda_codec *codec;
	पूर्णांक step;
पूर्ण;

/* initialize the follower volume with 0dB via snd_ctl_apply_vmaster_followers() */
अटल पूर्णांक init_follower_0dB(काष्ठा snd_kcontrol *follower,
			     काष्ठा snd_kcontrol *kctl,
			     व्योम *_arg)
अणु
	काष्ठा follower_init_arg *arg = _arg;
	पूर्णांक _tlv[4];
	स्थिर पूर्णांक *tlv = शून्य;
	पूर्णांक step;
	पूर्णांक val;

	अगर (kctl->vd[0].access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) अणु
		अगर (kctl->tlv.c != snd_hda_mixer_amp_tlv) अणु
			codec_err(arg->codec,
				  "Unexpected TLV callback for follower %s:%d\n",
				  kctl->id.name, kctl->id.index);
			वापस 0; /* ignore */
		पूर्ण
		get_ctl_amp_tlv(kctl, _tlv);
		tlv = _tlv;
	पूर्ण अन्यथा अगर (kctl->vd[0].access & SNDRV_CTL_ELEM_ACCESS_TLV_READ)
		tlv = kctl->tlv.p;

	अगर (!tlv || tlv[SNDRV_CTL_TLVO_TYPE] != SNDRV_CTL_TLVT_DB_SCALE)
		वापस 0;

	step = tlv[SNDRV_CTL_TLVO_DB_SCALE_MUTE_AND_STEP];
	step &= ~TLV_DB_SCALE_MUTE;
	अगर (!step)
		वापस 0;
	अगर (arg->step && arg->step != step) अणु
		codec_err(arg->codec,
			  "Mismatching dB step for vmaster follower (%d!=%d)\n",
			  arg->step, step);
		वापस 0;
	पूर्ण

	arg->step = step;
	val = -tlv[SNDRV_CTL_TLVO_DB_SCALE_MIN] / step;
	अगर (val > 0) अणु
		put_kctl_with_value(follower, val);
		वापस val;
	पूर्ण

	वापस 0;
पूर्ण

/* unmute the follower via snd_ctl_apply_vmaster_followers() */
अटल पूर्णांक init_follower_unmute(काष्ठा snd_kcontrol *follower,
				काष्ठा snd_kcontrol *kctl,
				व्योम *_arg)
अणु
	वापस put_kctl_with_value(follower, 1);
पूर्ण

अटल पूर्णांक add_follower(काष्ठा hda_codec *codec,
			व्योम *data, काष्ठा snd_kcontrol *follower)
अणु
	वापस snd_ctl_add_follower(data, follower);
पूर्ण

/**
 * __snd_hda_add_vmaster - create a भव master control and add followers
 * @codec: HD-audio codec
 * @name: vmaster control name
 * @tlv: TLV data (optional)
 * @followers: follower control names (optional)
 * @suffix: suffix string to each follower name (optional)
 * @init_follower_vol: initialize followers to unmute/0dB
 * @access: kcontrol access rights
 * @ctl_ret: store the vmaster kcontrol in वापस
 *
 * Create a भव master control with the given name.  The TLV data
 * must be either शून्य or a valid data.
 *
 * @followers is a शून्य-terminated array of strings, each of which is a
 * follower control name.  All controls with these names are asचिन्हित to
 * the new भव master control.
 *
 * This function वापसs zero अगर successful or a negative error code.
 */
पूर्णांक __snd_hda_add_vmaster(काष्ठा hda_codec *codec, अक्षर *name,
			  अचिन्हित पूर्णांक *tlv, स्थिर अक्षर * स्थिर *followers,
			  स्थिर अक्षर *suffix, bool init_follower_vol,
			  अचिन्हित पूर्णांक access, काष्ठा snd_kcontrol **ctl_ret)
अणु
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक err;

	अगर (ctl_ret)
		*ctl_ret = शून्य;

	err = map_followers(codec, followers, suffix, check_follower_present, शून्य);
	अगर (err != 1) अणु
		codec_dbg(codec, "No follower found for %s\n", name);
		वापस 0;
	पूर्ण
	kctl = snd_ctl_make_भव_master(name, tlv);
	अगर (!kctl)
		वापस -ENOMEM;
	kctl->vd[0].access |= access;
	err = snd_hda_ctl_add(codec, 0, kctl);
	अगर (err < 0)
		वापस err;

	err = map_followers(codec, followers, suffix, add_follower, kctl);
	अगर (err < 0)
		वापस err;

	/* init with master mute & zero volume */
	put_kctl_with_value(kctl, 0);
	अगर (init_follower_vol) अणु
		काष्ठा follower_init_arg arg = अणु
			.codec = codec,
			.step = 0,
		पूर्ण;
		snd_ctl_apply_vmaster_followers(kctl,
						tlv ? init_follower_0dB : init_follower_unmute,
						&arg);
	पूर्ण

	अगर (ctl_ret)
		*ctl_ret = kctl;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__snd_hda_add_vmaster);

/* meta hook to call each driver's vmaster hook */
अटल व्योम vmaster_hook(व्योम *निजी_data, पूर्णांक enabled)
अणु
	काष्ठा hda_vmaster_mute_hook *hook = निजी_data;

	hook->hook(hook->codec, enabled);
पूर्ण

/**
 * snd_hda_add_vmaster_hook - Add a vmaster hw specअगरic hook
 * @codec: the HDA codec
 * @hook: the vmaster hook object
 *
 * Add a hw specअगरic hook (like EAPD) with the given vmaster चयन kctl.
 */
पूर्णांक snd_hda_add_vmaster_hook(काष्ठा hda_codec *codec,
			     काष्ठा hda_vmaster_mute_hook *hook)
अणु
	अगर (!hook->hook || !hook->sw_kctl)
		वापस 0;
	hook->codec = codec;
	snd_ctl_add_vmaster_hook(hook->sw_kctl, vmaster_hook, hook);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_add_vmaster_hook);

/**
 * snd_hda_sync_vmaster_hook - Sync vmaster hook
 * @hook: the vmaster hook
 *
 * Call the hook with the current value क्रम synchronization.
 * Should be called in init callback.
 */
व्योम snd_hda_sync_vmaster_hook(काष्ठा hda_vmaster_mute_hook *hook)
अणु
	अगर (!hook->hook || !hook->codec)
		वापस;
	/* करोn't call vmaster hook in the deकाष्ठाor since it might have
	 * been alपढ़ोy destroyed
	 */
	अगर (hook->codec->bus->shutकरोwn)
		वापस;
	snd_ctl_sync_vmaster_hook(hook->sw_kctl);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_sync_vmaster_hook);


/**
 * snd_hda_mixer_amp_चयन_info - Info callback क्रम a standard AMP mixer चयन
 * @kcontrol: referred ctl element
 * @uinfo: poपूर्णांकer to get/store the data
 *
 * The control element is supposed to have the निजी_value field
 * set up via HDA_COMPOSE_AMP_VAL*() or related macros.
 */
पूर्णांक snd_hda_mixer_amp_चयन_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक chs = get_amp_channels(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = chs == 3 ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_mixer_amp_चयन_info);

/**
 * snd_hda_mixer_amp_चयन_get - Get callback क्रम a standard AMP mixer चयन
 * @kcontrol: ctl element
 * @ucontrol: poपूर्णांकer to get/store the data
 *
 * The control element is supposed to have the निजी_value field
 * set up via HDA_COMPOSE_AMP_VAL*() or related macros.
 */
पूर्णांक snd_hda_mixer_amp_चयन_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक chs = get_amp_channels(kcontrol);
	पूर्णांक dir = get_amp_direction(kcontrol);
	पूर्णांक idx = get_amp_index(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;

	अगर (chs & 1)
		*valp++ = (snd_hda_codec_amp_पढ़ो(codec, nid, 0, dir, idx) &
			   HDA_AMP_MUTE) ? 0 : 1;
	अगर (chs & 2)
		*valp = (snd_hda_codec_amp_पढ़ो(codec, nid, 1, dir, idx) &
			 HDA_AMP_MUTE) ? 0 : 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_mixer_amp_चयन_get);

/**
 * snd_hda_mixer_amp_चयन_put - Put callback क्रम a standard AMP mixer चयन
 * @kcontrol: ctl element
 * @ucontrol: poपूर्णांकer to get/store the data
 *
 * The control element is supposed to have the निजी_value field
 * set up via HDA_COMPOSE_AMP_VAL*() or related macros.
 */
पूर्णांक snd_hda_mixer_amp_चयन_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक chs = get_amp_channels(kcontrol);
	पूर्णांक dir = get_amp_direction(kcontrol);
	पूर्णांक idx = get_amp_index(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	पूर्णांक change = 0;

	अगर (chs & 1) अणु
		change = snd_hda_codec_amp_update(codec, nid, 0, dir, idx,
						  HDA_AMP_MUTE,
						  *valp ? 0 : HDA_AMP_MUTE);
		valp++;
	पूर्ण
	अगर (chs & 2)
		change |= snd_hda_codec_amp_update(codec, nid, 1, dir, idx,
						   HDA_AMP_MUTE,
						   *valp ? 0 : HDA_AMP_MUTE);
	hda_call_check_घातer_status(codec, nid);
	वापस change;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_mixer_amp_चयन_put);

/*
 * SPDIF out controls
 */

अटल पूर्णांक snd_hda_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hda_spdअगर_cmask_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = IEC958_AES0_PROFESSIONAL |
					   IEC958_AES0_NONAUDIO |
					   IEC958_AES0_CON_EMPHASIS_5015 |
					   IEC958_AES0_CON_NOT_COPYRIGHT;
	ucontrol->value.iec958.status[1] = IEC958_AES1_CON_CATEGORY |
					   IEC958_AES1_CON_ORIGINAL;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hda_spdअगर_pmask_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = IEC958_AES0_PROFESSIONAL |
					   IEC958_AES0_NONAUDIO |
					   IEC958_AES0_PRO_EMPHASIS_5015;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hda_spdअगर_शेष_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = kcontrol->निजी_value;
	काष्ठा hda_spdअगर_out *spdअगर;

	अगर (WARN_ON(codec->spdअगर_out.used <= idx))
		वापस -EINVAL;
	mutex_lock(&codec->spdअगर_mutex);
	spdअगर = snd_array_elem(&codec->spdअगर_out, idx);
	ucontrol->value.iec958.status[0] = spdअगर->status & 0xff;
	ucontrol->value.iec958.status[1] = (spdअगर->status >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (spdअगर->status >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (spdअगर->status >> 24) & 0xff;
	mutex_unlock(&codec->spdअगर_mutex);

	वापस 0;
पूर्ण

/* convert from SPDIF status bits to HDA SPDIF bits
 * bit 0 (DigEn) is always set zero (to be filled later)
 */
अटल अचिन्हित लघु convert_from_spdअगर_status(अचिन्हित पूर्णांक sbits)
अणु
	अचिन्हित लघु val = 0;

	अगर (sbits & IEC958_AES0_PROFESSIONAL)
		val |= AC_DIG1_PROFESSIONAL;
	अगर (sbits & IEC958_AES0_NONAUDIO)
		val |= AC_DIG1_NONAUDIO;
	अगर (sbits & IEC958_AES0_PROFESSIONAL) अणु
		अगर ((sbits & IEC958_AES0_PRO_EMPHASIS) ==
		    IEC958_AES0_PRO_EMPHASIS_5015)
			val |= AC_DIG1_EMPHASIS;
	पूर्ण अन्यथा अणु
		अगर ((sbits & IEC958_AES0_CON_EMPHASIS) ==
		    IEC958_AES0_CON_EMPHASIS_5015)
			val |= AC_DIG1_EMPHASIS;
		अगर (!(sbits & IEC958_AES0_CON_NOT_COPYRIGHT))
			val |= AC_DIG1_COPYRIGHT;
		अगर (sbits & (IEC958_AES1_CON_ORIGINAL << 8))
			val |= AC_DIG1_LEVEL;
		val |= sbits & (IEC958_AES1_CON_CATEGORY << 8);
	पूर्ण
	वापस val;
पूर्ण

/* convert to SPDIF status bits from HDA SPDIF bits
 */
अटल अचिन्हित पूर्णांक convert_to_spdअगर_status(अचिन्हित लघु val)
अणु
	अचिन्हित पूर्णांक sbits = 0;

	अगर (val & AC_DIG1_NONAUDIO)
		sbits |= IEC958_AES0_NONAUDIO;
	अगर (val & AC_DIG1_PROFESSIONAL)
		sbits |= IEC958_AES0_PROFESSIONAL;
	अगर (sbits & IEC958_AES0_PROFESSIONAL) अणु
		अगर (val & AC_DIG1_EMPHASIS)
			sbits |= IEC958_AES0_PRO_EMPHASIS_5015;
	पूर्ण अन्यथा अणु
		अगर (val & AC_DIG1_EMPHASIS)
			sbits |= IEC958_AES0_CON_EMPHASIS_5015;
		अगर (!(val & AC_DIG1_COPYRIGHT))
			sbits |= IEC958_AES0_CON_NOT_COPYRIGHT;
		अगर (val & AC_DIG1_LEVEL)
			sbits |= (IEC958_AES1_CON_ORIGINAL << 8);
		sbits |= val & (0x7f << 8);
	पूर्ण
	वापस sbits;
पूर्ण

/* set digital convert verbs both क्रम the given NID and its followers */
अटल व्योम set_dig_out(काष्ठा hda_codec *codec, hda_nid_t nid,
			पूर्णांक mask, पूर्णांक val)
अणु
	स्थिर hda_nid_t *d;

	snd_hdac_regmap_update(&codec->core, nid, AC_VERB_SET_DIGI_CONVERT_1,
			       mask, val);
	d = codec->follower_dig_outs;
	अगर (!d)
		वापस;
	क्रम (; *d; d++)
		snd_hdac_regmap_update(&codec->core, *d,
				       AC_VERB_SET_DIGI_CONVERT_1, mask, val);
पूर्ण

अटल अंतरभूत व्योम set_dig_out_convert(काष्ठा hda_codec *codec, hda_nid_t nid,
				       पूर्णांक dig1, पूर्णांक dig2)
अणु
	अचिन्हित पूर्णांक mask = 0;
	अचिन्हित पूर्णांक val = 0;

	अगर (dig1 != -1) अणु
		mask |= 0xff;
		val = dig1;
	पूर्ण
	अगर (dig2 != -1) अणु
		mask |= 0xff00;
		val |= dig2 << 8;
	पूर्ण
	set_dig_out(codec, nid, mask, val);
पूर्ण

अटल पूर्णांक snd_hda_spdअगर_शेष_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = kcontrol->निजी_value;
	काष्ठा hda_spdअगर_out *spdअगर;
	hda_nid_t nid;
	अचिन्हित लघु val;
	पूर्णांक change;

	अगर (WARN_ON(codec->spdअगर_out.used <= idx))
		वापस -EINVAL;
	mutex_lock(&codec->spdअगर_mutex);
	spdअगर = snd_array_elem(&codec->spdअगर_out, idx);
	nid = spdअगर->nid;
	spdअगर->status = ucontrol->value.iec958.status[0] |
		((अचिन्हित पूर्णांक)ucontrol->value.iec958.status[1] << 8) |
		((अचिन्हित पूर्णांक)ucontrol->value.iec958.status[2] << 16) |
		((अचिन्हित पूर्णांक)ucontrol->value.iec958.status[3] << 24);
	val = convert_from_spdअगर_status(spdअगर->status);
	val |= spdअगर->ctls & 1;
	change = spdअगर->ctls != val;
	spdअगर->ctls = val;
	अगर (change && nid != (u16)-1)
		set_dig_out_convert(codec, nid, val & 0xff, (val >> 8) & 0xff);
	mutex_unlock(&codec->spdअगर_mutex);
	वापस change;
पूर्ण

#घोषणा snd_hda_spdअगर_out_चयन_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_hda_spdअगर_out_चयन_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = kcontrol->निजी_value;
	काष्ठा hda_spdअगर_out *spdअगर;

	अगर (WARN_ON(codec->spdअगर_out.used <= idx))
		वापस -EINVAL;
	mutex_lock(&codec->spdअगर_mutex);
	spdअगर = snd_array_elem(&codec->spdअगर_out, idx);
	ucontrol->value.पूर्णांकeger.value[0] = spdअगर->ctls & AC_DIG1_ENABLE;
	mutex_unlock(&codec->spdअगर_mutex);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम set_spdअगर_ctls(काष्ठा hda_codec *codec, hda_nid_t nid,
				  पूर्णांक dig1, पूर्णांक dig2)
अणु
	set_dig_out_convert(codec, nid, dig1, dig2);
	/* unmute amp चयन (अगर any) */
	अगर ((get_wcaps(codec, nid) & AC_WCAP_OUT_AMP) &&
	    (dig1 & AC_DIG1_ENABLE))
		snd_hda_codec_amp_stereo(codec, nid, HDA_OUTPUT, 0,
					    HDA_AMP_MUTE, 0);
पूर्ण

अटल पूर्णांक snd_hda_spdअगर_out_चयन_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = kcontrol->निजी_value;
	काष्ठा hda_spdअगर_out *spdअगर;
	hda_nid_t nid;
	अचिन्हित लघु val;
	पूर्णांक change;

	अगर (WARN_ON(codec->spdअगर_out.used <= idx))
		वापस -EINVAL;
	mutex_lock(&codec->spdअगर_mutex);
	spdअगर = snd_array_elem(&codec->spdअगर_out, idx);
	nid = spdअगर->nid;
	val = spdअगर->ctls & ~AC_DIG1_ENABLE;
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val |= AC_DIG1_ENABLE;
	change = spdअगर->ctls != val;
	spdअगर->ctls = val;
	अगर (change && nid != (u16)-1)
		set_spdअगर_ctls(codec, nid, val & 0xff, -1);
	mutex_unlock(&codec->spdअगर_mutex);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new dig_mixes[] = अणु
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, CON_MASK),
		.info = snd_hda_spdअगर_mask_info,
		.get = snd_hda_spdअगर_cmask_get,
	पूर्ण,
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, PRO_MASK),
		.info = snd_hda_spdअगर_mask_info,
		.get = snd_hda_spdअगर_pmask_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
		.info = snd_hda_spdअगर_mask_info,
		.get = snd_hda_spdअगर_शेष_get,
		.put = snd_hda_spdअगर_शेष_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, SWITCH),
		.info = snd_hda_spdअगर_out_चयन_info,
		.get = snd_hda_spdअगर_out_चयन_get,
		.put = snd_hda_spdअगर_out_चयन_put,
	पूर्ण,
	अणु पूर्ण /* end */
पूर्ण;

/**
 * snd_hda_create_dig_out_ctls - create Output SPDIF-related controls
 * @codec: the HDA codec
 * @associated_nid: NID that new ctls associated with
 * @cvt_nid: converter NID
 * @type: HDA_PCM_TYPE_*
 * Creates controls related with the digital output.
 * Called from each patch supporting the digital out.
 *
 * Returns 0 अगर successful, or a negative error code.
 */
पूर्णांक snd_hda_create_dig_out_ctls(काष्ठा hda_codec *codec,
				hda_nid_t associated_nid,
				hda_nid_t cvt_nid,
				पूर्णांक type)
अणु
	पूर्णांक err;
	काष्ठा snd_kcontrol *kctl;
	स्थिर काष्ठा snd_kcontrol_new *dig_mix;
	पूर्णांक idx = 0;
	पूर्णांक val = 0;
	स्थिर पूर्णांक spdअगर_index = 16;
	काष्ठा hda_spdअगर_out *spdअगर;
	काष्ठा hda_bus *bus = codec->bus;

	अगर (bus->primary_dig_out_type == HDA_PCM_TYPE_HDMI &&
	    type == HDA_PCM_TYPE_SPDIF) अणु
		idx = spdअगर_index;
	पूर्ण अन्यथा अगर (bus->primary_dig_out_type == HDA_PCM_TYPE_SPDIF &&
		   type == HDA_PCM_TYPE_HDMI) अणु
		/* suppose a single SPDIF device */
		क्रम (dig_mix = dig_mixes; dig_mix->name; dig_mix++) अणु
			kctl = find_mixer_ctl(codec, dig_mix->name, 0, 0);
			अगर (!kctl)
				अवरोध;
			kctl->id.index = spdअगर_index;
		पूर्ण
		bus->primary_dig_out_type = HDA_PCM_TYPE_HDMI;
	पूर्ण
	अगर (!bus->primary_dig_out_type)
		bus->primary_dig_out_type = type;

	idx = find_empty_mixer_ctl_idx(codec, "IEC958 Playback Switch", idx);
	अगर (idx < 0) अणु
		codec_err(codec, "too many IEC958 outputs\n");
		वापस -EBUSY;
	पूर्ण
	spdअगर = snd_array_new(&codec->spdअगर_out);
	अगर (!spdअगर)
		वापस -ENOMEM;
	क्रम (dig_mix = dig_mixes; dig_mix->name; dig_mix++) अणु
		kctl = snd_ctl_new1(dig_mix, codec);
		अगर (!kctl)
			वापस -ENOMEM;
		kctl->id.index = idx;
		kctl->निजी_value = codec->spdअगर_out.used - 1;
		err = snd_hda_ctl_add(codec, associated_nid, kctl);
		अगर (err < 0)
			वापस err;
	पूर्ण
	spdअगर->nid = cvt_nid;
	snd_hdac_regmap_पढ़ो(&codec->core, cvt_nid,
			     AC_VERB_GET_DIGI_CONVERT_1, &val);
	spdअगर->ctls = val;
	spdअगर->status = convert_to_spdअगर_status(spdअगर->ctls);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_create_dig_out_ctls);

/**
 * snd_hda_spdअगर_out_of_nid - get the hda_spdअगर_out entry from the given NID
 * @codec: the HDA codec
 * @nid: widget NID
 *
 * call within spdअगर_mutex lock
 */
काष्ठा hda_spdअगर_out *snd_hda_spdअगर_out_of_nid(काष्ठा hda_codec *codec,
					       hda_nid_t nid)
अणु
	काष्ठा hda_spdअगर_out *spdअगर;
	पूर्णांक i;

	snd_array_क्रम_each(&codec->spdअगर_out, i, spdअगर) अणु
		अगर (spdअगर->nid == nid)
			वापस spdअगर;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_spdअगर_out_of_nid);

/**
 * snd_hda_spdअगर_ctls_unassign - Unassign the given SPDIF ctl
 * @codec: the HDA codec
 * @idx: the SPDIF ctl index
 *
 * Unassign the widget from the given SPDIF control.
 */
व्योम snd_hda_spdअगर_ctls_unassign(काष्ठा hda_codec *codec, पूर्णांक idx)
अणु
	काष्ठा hda_spdअगर_out *spdअगर;

	अगर (WARN_ON(codec->spdअगर_out.used <= idx))
		वापस;
	mutex_lock(&codec->spdअगर_mutex);
	spdअगर = snd_array_elem(&codec->spdअगर_out, idx);
	spdअगर->nid = (u16)-1;
	mutex_unlock(&codec->spdअगर_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_spdअगर_ctls_unassign);

/**
 * snd_hda_spdअगर_ctls_assign - Assign the SPDIF controls to the given NID
 * @codec: the HDA codec
 * @idx: the SPDIF ctl idx
 * @nid: widget NID
 *
 * Assign the widget to the SPDIF control with the given index.
 */
व्योम snd_hda_spdअगर_ctls_assign(काष्ठा hda_codec *codec, पूर्णांक idx, hda_nid_t nid)
अणु
	काष्ठा hda_spdअगर_out *spdअगर;
	अचिन्हित लघु val;

	अगर (WARN_ON(codec->spdअगर_out.used <= idx))
		वापस;
	mutex_lock(&codec->spdअगर_mutex);
	spdअगर = snd_array_elem(&codec->spdअगर_out, idx);
	अगर (spdअगर->nid != nid) अणु
		spdअगर->nid = nid;
		val = spdअगर->ctls;
		set_spdअगर_ctls(codec, nid, val & 0xff, (val >> 8) & 0xff);
	पूर्ण
	mutex_unlock(&codec->spdअगर_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_spdअगर_ctls_assign);

/*
 * SPDIF sharing with analog output
 */
अटल पूर्णांक spdअगर_share_sw_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_multi_out *mout = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = mout->share_spdअगर;
	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_share_sw_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_multi_out *mout = snd_kcontrol_chip(kcontrol);
	mout->share_spdअगर = !!ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new spdअगर_share_sw = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "IEC958 Default PCM Playback Switch",
	.info = snd_ctl_boolean_mono_info,
	.get = spdअगर_share_sw_get,
	.put = spdअगर_share_sw_put,
पूर्ण;

/**
 * snd_hda_create_spdअगर_share_sw - create Default PCM चयन
 * @codec: the HDA codec
 * @mout: multi-out instance
 */
पूर्णांक snd_hda_create_spdअगर_share_sw(काष्ठा hda_codec *codec,
				  काष्ठा hda_multi_out *mout)
अणु
	काष्ठा snd_kcontrol *kctl;

	अगर (!mout->dig_out_nid)
		वापस 0;

	kctl = snd_ctl_new1(&spdअगर_share_sw, mout);
	अगर (!kctl)
		वापस -ENOMEM;
	/* ATTENTION: here mout is passed as निजी_data, instead of codec */
	वापस snd_hda_ctl_add(codec, mout->dig_out_nid, kctl);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_create_spdअगर_share_sw);

/*
 * SPDIF input
 */

#घोषणा snd_hda_spdअगर_in_चयन_info	snd_hda_spdअगर_out_चयन_info

अटल पूर्णांक snd_hda_spdअगर_in_चयन_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = codec->spdअगर_in_enable;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hda_spdअगर_in_चयन_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->निजी_value;
	अचिन्हित पूर्णांक val = !!ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक change;

	mutex_lock(&codec->spdअगर_mutex);
	change = codec->spdअगर_in_enable != val;
	अगर (change) अणु
		codec->spdअगर_in_enable = val;
		snd_hdac_regmap_ग_लिखो(&codec->core, nid,
				      AC_VERB_SET_DIGI_CONVERT_1, val);
	पूर्ण
	mutex_unlock(&codec->spdअगर_mutex);
	वापस change;
पूर्ण

अटल पूर्णांक snd_hda_spdअगर_in_status_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->निजी_value;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक sbits;

	snd_hdac_regmap_पढ़ो(&codec->core, nid,
			     AC_VERB_GET_DIGI_CONVERT_1, &val);
	sbits = convert_to_spdअगर_status(val);
	ucontrol->value.iec958.status[0] = sbits;
	ucontrol->value.iec958.status[1] = sbits >> 8;
	ucontrol->value.iec958.status[2] = sbits >> 16;
	ucontrol->value.iec958.status[3] = sbits >> 24;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new dig_in_ctls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, SWITCH),
		.info = snd_hda_spdअगर_in_चयन_info,
		.get = snd_hda_spdअगर_in_चयन_get,
		.put = snd_hda_spdअगर_in_चयन_put,
	पूर्ण,
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, DEFAULT),
		.info = snd_hda_spdअगर_mask_info,
		.get = snd_hda_spdअगर_in_status_get,
	पूर्ण,
	अणु पूर्ण /* end */
पूर्ण;

/**
 * snd_hda_create_spdअगर_in_ctls - create Input SPDIF-related controls
 * @codec: the HDA codec
 * @nid: audio in widget NID
 *
 * Creates controls related with the SPDIF input.
 * Called from each patch supporting the SPDIF in.
 *
 * Returns 0 अगर successful, or a negative error code.
 */
पूर्णांक snd_hda_create_spdअगर_in_ctls(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	पूर्णांक err;
	काष्ठा snd_kcontrol *kctl;
	स्थिर काष्ठा snd_kcontrol_new *dig_mix;
	पूर्णांक idx;

	idx = find_empty_mixer_ctl_idx(codec, "IEC958 Capture Switch", 0);
	अगर (idx < 0) अणु
		codec_err(codec, "too many IEC958 inputs\n");
		वापस -EBUSY;
	पूर्ण
	क्रम (dig_mix = dig_in_ctls; dig_mix->name; dig_mix++) अणु
		kctl = snd_ctl_new1(dig_mix, codec);
		अगर (!kctl)
			वापस -ENOMEM;
		kctl->निजी_value = nid;
		err = snd_hda_ctl_add(codec, nid, kctl);
		अगर (err < 0)
			वापस err;
	पूर्ण
	codec->spdअगर_in_enable =
		snd_hda_codec_पढ़ो(codec, nid, 0,
				   AC_VERB_GET_DIGI_CONVERT_1, 0) &
		AC_DIG1_ENABLE;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_create_spdअगर_in_ctls);

/**
 * snd_hda_codec_set_घातer_to_all - Set the घातer state to all widमाला_लो
 * @codec: the HDA codec
 * @fg: function group (not used now)
 * @घातer_state: the घातer state to set (AC_PWRST_*)
 *
 * Set the given घातer state to all widमाला_लो that have the घातer control.
 * If the codec has घातer_filter set, it evaluates the घातer state and
 * filter out अगर it's unchanged as D3.
 */
व्योम snd_hda_codec_set_घातer_to_all(काष्ठा hda_codec *codec, hda_nid_t fg,
				    अचिन्हित पूर्णांक घातer_state)
अणु
	hda_nid_t nid;

	क्रम_each_hda_codec_node(nid, codec) अणु
		अचिन्हित पूर्णांक wcaps = get_wcaps(codec, nid);
		अचिन्हित पूर्णांक state = घातer_state;
		अगर (!(wcaps & AC_WCAP_POWER))
			जारी;
		अगर (codec->घातer_filter) अणु
			state = codec->घातer_filter(codec, nid, घातer_state);
			अगर (state != घातer_state && घातer_state == AC_PWRST_D3)
				जारी;
		पूर्ण
		snd_hda_codec_ग_लिखो(codec, nid, 0, AC_VERB_SET_POWER_STATE,
				    state);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_set_घातer_to_all);

/**
 * snd_hda_codec_eapd_घातer_filter - A घातer filter callback क्रम EAPD
 * @codec: the HDA codec
 * @nid: widget NID
 * @घातer_state: घातer state to evalue
 *
 * Don't घातer करोwn the widget अगर it controls eapd and EAPD_BTLENABLE is set.
 * This can be used a codec घातer_filter callback.
 */
अचिन्हित पूर्णांक snd_hda_codec_eapd_घातer_filter(काष्ठा hda_codec *codec,
					     hda_nid_t nid,
					     अचिन्हित पूर्णांक घातer_state)
अणु
	अगर (nid == codec->core.afg || nid == codec->core.mfg)
		वापस घातer_state;
	अगर (घातer_state == AC_PWRST_D3 &&
	    get_wcaps_type(get_wcaps(codec, nid)) == AC_WID_PIN &&
	    (snd_hda_query_pin_caps(codec, nid) & AC_PINCAP_EAPD)) अणु
		पूर्णांक eapd = snd_hda_codec_पढ़ो(codec, nid, 0,
					      AC_VERB_GET_EAPD_BTLENABLE, 0);
		अगर (eapd & 0x02)
			वापस AC_PWRST_D0;
	पूर्ण
	वापस घातer_state;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_eapd_घातer_filter);

/*
 * set घातer state of the codec, and वापस the घातer state
 */
अटल अचिन्हित पूर्णांक hda_set_घातer_state(काष्ठा hda_codec *codec,
					अचिन्हित पूर्णांक घातer_state)
अणु
	hda_nid_t fg = codec->core.afg ? codec->core.afg : codec->core.mfg;
	पूर्णांक count;
	अचिन्हित पूर्णांक state;
	पूर्णांक flags = 0;

	/* this delay seems necessary to aव्योम click noise at घातer-करोwn */
	अगर (घातer_state == AC_PWRST_D3) अणु
		अगर (codec->depop_delay < 0)
			msleep(codec_has_epss(codec) ? 10 : 100);
		अन्यथा अगर (codec->depop_delay > 0)
			msleep(codec->depop_delay);
		flags = HDA_RW_NO_RESPONSE_FALLBACK;
	पूर्ण

	/* repeat घातer states setting at most 10 बार*/
	क्रम (count = 0; count < 10; count++) अणु
		अगर (codec->patch_ops.set_घातer_state)
			codec->patch_ops.set_घातer_state(codec, fg,
							 घातer_state);
		अन्यथा अणु
			state = घातer_state;
			अगर (codec->घातer_filter)
				state = codec->घातer_filter(codec, fg, state);
			अगर (state == घातer_state || घातer_state != AC_PWRST_D3)
				snd_hda_codec_पढ़ो(codec, fg, flags,
						   AC_VERB_SET_POWER_STATE,
						   state);
			snd_hda_codec_set_घातer_to_all(codec, fg, घातer_state);
		पूर्ण
		state = snd_hda_sync_घातer_state(codec, fg, घातer_state);
		अगर (!(state & AC_PWRST_ERROR))
			अवरोध;
	पूर्ण

	वापस state;
पूर्ण

/* sync घातer states of all widमाला_लो;
 * this is called at the end of codec parsing
 */
अटल व्योम sync_घातer_up_states(काष्ठा hda_codec *codec)
अणु
	hda_nid_t nid;

	/* करोn't care अगर no filter is used */
	अगर (!codec->घातer_filter)
		वापस;

	क्रम_each_hda_codec_node(nid, codec) अणु
		अचिन्हित पूर्णांक wcaps = get_wcaps(codec, nid);
		अचिन्हित पूर्णांक target;
		अगर (!(wcaps & AC_WCAP_POWER))
			जारी;
		target = codec->घातer_filter(codec, nid, AC_PWRST_D0);
		अगर (target == AC_PWRST_D0)
			जारी;
		अगर (!snd_hda_check_घातer_state(codec, nid, target))
			snd_hda_codec_ग_लिखो(codec, nid, 0,
					    AC_VERB_SET_POWER_STATE, target);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SND_HDA_RECONFIG
/* execute additional init verbs */
अटल व्योम hda_exec_init_verbs(काष्ठा hda_codec *codec)
अणु
	अगर (codec->init_verbs.list)
		snd_hda_sequence_ग_लिखो(codec, codec->init_verbs.list);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम hda_exec_init_verbs(काष्ठा hda_codec *codec) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
/* update the घातer on/off account with the current jअगरfies */
अटल व्योम update_घातer_acct(काष्ठा hda_codec *codec, bool on)
अणु
	अचिन्हित दीर्घ delta = jअगरfies - codec->घातer_jअगरfies;

	अगर (on)
		codec->घातer_on_acct += delta;
	अन्यथा
		codec->घातer_off_acct += delta;
	codec->घातer_jअगरfies += delta;
पूर्ण

व्योम snd_hda_update_घातer_acct(काष्ठा hda_codec *codec)
अणु
	update_घातer_acct(codec, hda_codec_is_घातer_on(codec));
पूर्ण

/*
 * call suspend and घातer-करोwn; used both from PM and घातer-save
 * this function वापसs the घातer state in the end
 */
अटल अचिन्हित पूर्णांक hda_call_codec_suspend(काष्ठा hda_codec *codec)
अणु
	अचिन्हित पूर्णांक state;

	snd_hdac_enter_pm(&codec->core);
	अगर (codec->patch_ops.suspend)
		codec->patch_ops.suspend(codec);
	hda_cleanup_all_streams(codec);
	state = hda_set_घातer_state(codec, AC_PWRST_D3);
	update_घातer_acct(codec, true);
	snd_hdac_leave_pm(&codec->core);
	वापस state;
पूर्ण

/*
 * kick up codec; used both from PM and घातer-save
 */
अटल व्योम hda_call_codec_resume(काष्ठा hda_codec *codec)
अणु
	snd_hdac_enter_pm(&codec->core);
	अगर (codec->core.regmap)
		regcache_mark_dirty(codec->core.regmap);

	codec->घातer_jअगरfies = jअगरfies;

	hda_set_घातer_state(codec, AC_PWRST_D0);
	restore_shutup_pins(codec);
	hda_exec_init_verbs(codec);
	snd_hda_jack_set_dirty_all(codec);
	अगर (codec->patch_ops.resume)
		codec->patch_ops.resume(codec);
	अन्यथा अणु
		अगर (codec->patch_ops.init)
			codec->patch_ops.init(codec);
		snd_hda_regmap_sync(codec);
	पूर्ण

	अगर (codec->jackpoll_पूर्णांकerval)
		hda_jackpoll_work(&codec->jackpoll_work.work);
	अन्यथा
		snd_hda_jack_report_sync(codec);
	codec->core.dev.घातer.घातer_state = PMSG_ON;
	snd_hdac_leave_pm(&codec->core);
पूर्ण

अटल पूर्णांक hda_codec_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा hda_codec *codec = dev_to_hda_codec(dev);
	अचिन्हित पूर्णांक state;

	/* Nothing to करो अगर card registration fails and the component driver never probes */
	अगर (!codec->card)
		वापस 0;

	cancel_delayed_work_sync(&codec->jackpoll_work);
	state = hda_call_codec_suspend(codec);
	अगर (codec->link_करोwn_at_suspend ||
	    (codec_has_clkstop(codec) && codec_has_epss(codec) &&
	     (state & AC_PWRST_CLK_STOP_OK)))
		snd_hdac_codec_link_करोwn(&codec->core);
	codec_display_घातer(codec, false);
	वापस 0;
पूर्ण

अटल पूर्णांक hda_codec_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा hda_codec *codec = dev_to_hda_codec(dev);

	/* Nothing to करो अगर card registration fails and the component driver never probes */
	अगर (!codec->card)
		वापस 0;

	codec_display_घातer(codec, true);
	snd_hdac_codec_link_up(&codec->core);
	hda_call_codec_resume(codec);
	pm_runसमय_mark_last_busy(dev);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक hda_codec_pm_prepare(काष्ठा device *dev)
अणु
	dev->घातer.घातer_state = PMSG_SUSPEND;
	वापस pm_runसमय_suspended(dev);
पूर्ण

अटल व्योम hda_codec_pm_complete(काष्ठा device *dev)
अणु
	काष्ठा hda_codec *codec = dev_to_hda_codec(dev);

	/* If no other pm-functions are called between prepare() and complete() */
	अगर (dev->घातer.घातer_state.event == PM_EVENT_SUSPEND)
		dev->घातer.घातer_state = PMSG_RESUME;

	अगर (pm_runसमय_suspended(dev) && (codec->jackpoll_पूर्णांकerval ||
	    hda_codec_need_resume(codec) || codec->क्रमced_resume))
		pm_request_resume(dev);
पूर्ण

अटल पूर्णांक hda_codec_pm_suspend(काष्ठा device *dev)
अणु
	dev->घातer.घातer_state = PMSG_SUSPEND;
	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक hda_codec_pm_resume(काष्ठा device *dev)
अणु
	dev->घातer.घातer_state = PMSG_RESUME;
	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण

अटल पूर्णांक hda_codec_pm_मुक्तze(काष्ठा device *dev)
अणु
	dev->घातer.घातer_state = PMSG_FREEZE;
	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक hda_codec_pm_thaw(काष्ठा device *dev)
अणु
	dev->घातer.घातer_state = PMSG_THAW;
	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण

अटल पूर्णांक hda_codec_pm_restore(काष्ठा device *dev)
अणु
	dev->घातer.घातer_state = PMSG_RESTORE;
	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

/* referred in hda_bind.c */
स्थिर काष्ठा dev_pm_ops hda_codec_driver_pm = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.prepare = hda_codec_pm_prepare,
	.complete = hda_codec_pm_complete,
	.suspend = hda_codec_pm_suspend,
	.resume = hda_codec_pm_resume,
	.मुक्तze = hda_codec_pm_मुक्तze,
	.thaw = hda_codec_pm_thaw,
	.घातeroff = hda_codec_pm_suspend,
	.restore = hda_codec_pm_restore,
#पूर्ण_अगर /* CONFIG_PM_SLEEP */
	SET_RUNTIME_PM_OPS(hda_codec_runसमय_suspend, hda_codec_runसमय_resume,
			   शून्य)
पूर्ण;

/*
 * add standard channel maps अगर not specअगरied
 */
अटल पूर्णांक add_std_chmaps(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_pcm *pcm;
	पूर्णांक str, err;

	list_क्रम_each_entry(pcm, &codec->pcm_list_head, list) अणु
		क्रम (str = 0; str < 2; str++) अणु
			काष्ठा hda_pcm_stream *hinfo = &pcm->stream[str];
			काष्ठा snd_pcm_chmap *chmap;
			स्थिर काष्ठा snd_pcm_chmap_elem *elem;

			अगर (!pcm->pcm || pcm->own_chmap || !hinfo->substreams)
				जारी;
			elem = hinfo->chmap ? hinfo->chmap : snd_pcm_std_chmaps;
			err = snd_pcm_add_chmap_ctls(pcm->pcm, str, elem,
						     hinfo->channels_max,
						     0, &chmap);
			अगर (err < 0)
				वापस err;
			chmap->channel_mask = SND_PCM_CHMAP_MASK_2468;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* शेष channel maps क्रम 2.1 speakers;
 * since HD-audio supports only stereo, odd number channels are omitted
 */
स्थिर काष्ठा snd_pcm_chmap_elem snd_pcm_2_1_chmaps[] = अणु
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR पूर्ण पूर्ण,
	अणु .channels = 4,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
		   SNDRV_CHMAP_LFE, SNDRV_CHMAP_LFE पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;
EXPORT_SYMBOL_GPL(snd_pcm_2_1_chmaps);

पूर्णांक snd_hda_codec_build_controls(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err = 0;
	hda_exec_init_verbs(codec);
	/* जारी to initialize... */
	अगर (codec->patch_ops.init)
		err = codec->patch_ops.init(codec);
	अगर (!err && codec->patch_ops.build_controls)
		err = codec->patch_ops.build_controls(codec);
	अगर (err < 0)
		वापस err;

	/* we create chmaps here instead of build_pcms */
	err = add_std_chmaps(codec);
	अगर (err < 0)
		वापस err;

	अगर (codec->jackpoll_पूर्णांकerval)
		hda_jackpoll_work(&codec->jackpoll_work.work);
	अन्यथा
		snd_hda_jack_report_sync(codec); /* call at the last init poपूर्णांक */
	sync_घातer_up_states(codec);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_build_controls);

/*
 * PCM stuff
 */
अटल पूर्णांक hda_pcm_शेष_खोलो_बंद(काष्ठा hda_pcm_stream *hinfo,
				      काष्ठा hda_codec *codec,
				      काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक hda_pcm_शेष_prepare(काष्ठा hda_pcm_stream *hinfo,
				   काष्ठा hda_codec *codec,
				   अचिन्हित पूर्णांक stream_tag,
				   अचिन्हित पूर्णांक क्रमmat,
				   काष्ठा snd_pcm_substream *substream)
अणु
	snd_hda_codec_setup_stream(codec, hinfo->nid, stream_tag, 0, क्रमmat);
	वापस 0;
पूर्ण

अटल पूर्णांक hda_pcm_शेष_cleanup(काष्ठा hda_pcm_stream *hinfo,
				   काष्ठा hda_codec *codec,
				   काष्ठा snd_pcm_substream *substream)
अणु
	snd_hda_codec_cleanup_stream(codec, hinfo->nid);
	वापस 0;
पूर्ण

अटल पूर्णांक set_pcm_शेष_values(काष्ठा hda_codec *codec,
				  काष्ठा hda_pcm_stream *info)
अणु
	पूर्णांक err;

	/* query support PCM inक्रमmation from the given NID */
	अगर (info->nid && (!info->rates || !info->क्रमmats)) अणु
		err = snd_hda_query_supported_pcm(codec, info->nid,
				info->rates ? शून्य : &info->rates,
				info->क्रमmats ? शून्य : &info->क्रमmats,
				info->maxbps ? शून्य : &info->maxbps);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (info->ops.खोलो == शून्य)
		info->ops.खोलो = hda_pcm_शेष_खोलो_बंद;
	अगर (info->ops.बंद == शून्य)
		info->ops.बंद = hda_pcm_शेष_खोलो_बंद;
	अगर (info->ops.prepare == शून्य) अणु
		अगर (snd_BUG_ON(!info->nid))
			वापस -EINVAL;
		info->ops.prepare = hda_pcm_शेष_prepare;
	पूर्ण
	अगर (info->ops.cleanup == शून्य) अणु
		अगर (snd_BUG_ON(!info->nid))
			वापस -EINVAL;
		info->ops.cleanup = hda_pcm_शेष_cleanup;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * codec prepare/cleanup entries
 */
/**
 * snd_hda_codec_prepare - Prepare a stream
 * @codec: the HDA codec
 * @hinfo: PCM inक्रमmation
 * @stream: stream tag to assign
 * @क्रमmat: क्रमmat id to assign
 * @substream: PCM substream to assign
 *
 * Calls the prepare callback set by the codec with the given arguments.
 * Clean up the inactive streams when successful.
 */
पूर्णांक snd_hda_codec_prepare(काष्ठा hda_codec *codec,
			  काष्ठा hda_pcm_stream *hinfo,
			  अचिन्हित पूर्णांक stream,
			  अचिन्हित पूर्णांक क्रमmat,
			  काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक ret;
	mutex_lock(&codec->bus->prepare_mutex);
	अगर (hinfo->ops.prepare)
		ret = hinfo->ops.prepare(hinfo, codec, stream, क्रमmat,
					 substream);
	अन्यथा
		ret = -ENODEV;
	अगर (ret >= 0)
		purअगरy_inactive_streams(codec);
	mutex_unlock(&codec->bus->prepare_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_prepare);

/**
 * snd_hda_codec_cleanup - Clean up stream resources
 * @codec: the HDA codec
 * @hinfo: PCM inक्रमmation
 * @substream: PCM substream
 *
 * Calls the cleanup callback set by the codec with the given arguments.
 */
व्योम snd_hda_codec_cleanup(काष्ठा hda_codec *codec,
			   काष्ठा hda_pcm_stream *hinfo,
			   काष्ठा snd_pcm_substream *substream)
अणु
	mutex_lock(&codec->bus->prepare_mutex);
	अगर (hinfo->ops.cleanup)
		hinfo->ops.cleanup(hinfo, codec, substream);
	mutex_unlock(&codec->bus->prepare_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_cleanup);

/* global */
स्थिर अक्षर *snd_hda_pcm_type_name[HDA_PCM_NTYPES] = अणु
	"Audio", "SPDIF", "HDMI", "Modem"
पूर्ण;

/*
 * get the empty PCM device number to assign
 */
अटल पूर्णांक get_empty_pcm_device(काष्ठा hda_bus *bus, अचिन्हित पूर्णांक type)
अणु
	/* audio device indices; not linear to keep compatibility */
	/* asचिन्हित to अटल slots up to dev#10; अगर more needed, assign
	 * the later slot dynamically (when CONFIG_SND_DYNAMIC_MINORS=y)
	 */
	अटल स्थिर पूर्णांक audio_idx[HDA_PCM_NTYPES][5] = अणु
		[HDA_PCM_TYPE_AUDIO] = अणु 0, 2, 4, 5, -1 पूर्ण,
		[HDA_PCM_TYPE_SPDIF] = अणु 1, -1 पूर्ण,
		[HDA_PCM_TYPE_HDMI]  = अणु 3, 7, 8, 9, -1 पूर्ण,
		[HDA_PCM_TYPE_MODEM] = अणु 6, -1 पूर्ण,
	पूर्ण;
	पूर्णांक i;

	अगर (type >= HDA_PCM_NTYPES) अणु
		dev_err(bus->card->dev, "Invalid PCM type %d\n", type);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; audio_idx[type][i] >= 0; i++) अणु
#अगर_अघोषित CONFIG_SND_DYNAMIC_MINORS
		अगर (audio_idx[type][i] >= 8)
			अवरोध;
#पूर्ण_अगर
		अगर (!test_and_set_bit(audio_idx[type][i], bus->pcm_dev_bits))
			वापस audio_idx[type][i];
	पूर्ण

#अगर_घोषित CONFIG_SND_DYNAMIC_MINORS
	/* non-fixed slots starting from 10 */
	क्रम (i = 10; i < 32; i++) अणु
		अगर (!test_and_set_bit(i, bus->pcm_dev_bits))
			वापस i;
	पूर्ण
#पूर्ण_अगर

	dev_warn(bus->card->dev, "Too many %s devices\n",
		snd_hda_pcm_type_name[type]);
#अगर_अघोषित CONFIG_SND_DYNAMIC_MINORS
	dev_warn(bus->card->dev,
		 "Consider building the kernel with CONFIG_SND_DYNAMIC_MINORS=y\n");
#पूर्ण_अगर
	वापस -EAGAIN;
पूर्ण

/* call build_pcms ops of the given codec and set up the शेष parameters */
पूर्णांक snd_hda_codec_parse_pcms(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_pcm *cpcm;
	पूर्णांक err;

	अगर (!list_empty(&codec->pcm_list_head))
		वापस 0; /* alपढ़ोy parsed */

	अगर (!codec->patch_ops.build_pcms)
		वापस 0;

	err = codec->patch_ops.build_pcms(codec);
	अगर (err < 0) अणु
		codec_err(codec, "cannot build PCMs for #%d (error %d)\n",
			  codec->core.addr, err);
		वापस err;
	पूर्ण

	list_क्रम_each_entry(cpcm, &codec->pcm_list_head, list) अणु
		पूर्णांक stream;

		क्रम (stream = 0; stream < 2; stream++) अणु
			काष्ठा hda_pcm_stream *info = &cpcm->stream[stream];

			अगर (!info->substreams)
				जारी;
			err = set_pcm_शेष_values(codec, info);
			अगर (err < 0) अणु
				codec_warn(codec,
					   "fail to setup default for PCM %s\n",
					   cpcm->name);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_codec_parse_pcms);

/* assign all PCMs of the given codec */
पूर्णांक snd_hda_codec_build_pcms(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_bus *bus = codec->bus;
	काष्ठा hda_pcm *cpcm;
	पूर्णांक dev, err;

	err = snd_hda_codec_parse_pcms(codec);
	अगर (err < 0)
		वापस err;

	/* attach a new PCM streams */
	list_क्रम_each_entry(cpcm, &codec->pcm_list_head, list) अणु
		अगर (cpcm->pcm)
			जारी; /* alपढ़ोy attached */
		अगर (!cpcm->stream[0].substreams && !cpcm->stream[1].substreams)
			जारी; /* no substreams asचिन्हित */

		dev = get_empty_pcm_device(bus, cpcm->pcm_type);
		अगर (dev < 0) अणु
			cpcm->device = SNDRV_PCM_INVALID_DEVICE;
			जारी; /* no fatal error */
		पूर्ण
		cpcm->device = dev;
		err =  snd_hda_attach_pcm_stream(bus, codec, cpcm);
		अगर (err < 0) अणु
			codec_err(codec,
				  "cannot attach PCM stream %d for codec #%d\n",
				  dev, codec->core.addr);
			जारी; /* no fatal error */
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * snd_hda_add_new_ctls - create controls from the array
 * @codec: the HDA codec
 * @knew: the array of काष्ठा snd_kcontrol_new
 *
 * This helper function creates and add new controls in the given array.
 * The array must be terminated with an empty entry as terminator.
 *
 * Returns 0 अगर successful, or a negative error code.
 */
पूर्णांक snd_hda_add_new_ctls(काष्ठा hda_codec *codec,
			 स्थिर काष्ठा snd_kcontrol_new *knew)
अणु
	पूर्णांक err;

	क्रम (; knew->name; knew++) अणु
		काष्ठा snd_kcontrol *kctl;
		पूर्णांक addr = 0, idx = 0;
		अगर (knew->अगरace == (__क्रमce snd_ctl_elem_अगरace_t)-1)
			जारी; /* skip this codec निजी value */
		क्रम (;;) अणु
			kctl = snd_ctl_new1(knew, codec);
			अगर (!kctl)
				वापस -ENOMEM;
			अगर (addr > 0)
				kctl->id.device = addr;
			अगर (idx > 0)
				kctl->id.index = idx;
			err = snd_hda_ctl_add(codec, 0, kctl);
			अगर (!err)
				अवरोध;
			/* try first with another device index corresponding to
			 * the codec addr; अगर it still fails (or it's the
			 * primary codec), then try another control index
			 */
			अगर (!addr && codec->core.addr)
				addr = codec->core.addr;
			अन्यथा अगर (!idx && !knew->index) अणु
				idx = find_empty_mixer_ctl_idx(codec,
							       knew->name, 0);
				अगर (idx <= 0)
					वापस err;
			पूर्ण अन्यथा
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_add_new_ctls);

#अगर_घोषित CONFIG_PM
अटल व्योम codec_set_घातer_save(काष्ठा hda_codec *codec, पूर्णांक delay)
अणु
	काष्ठा device *dev = hda_codec_dev(codec);

	अगर (delay == 0 && codec->स्वतः_runसमय_pm)
		delay = 3000;

	अगर (delay > 0) अणु
		pm_runसमय_set_स्वतःsuspend_delay(dev, delay);
		pm_runसमय_use_स्वतःsuspend(dev);
		pm_runसमय_allow(dev);
		अगर (!pm_runसमय_suspended(dev))
			pm_runसमय_mark_last_busy(dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_करोnt_use_स्वतःsuspend(dev);
		pm_runसमय_क्रमbid(dev);
	पूर्ण
पूर्ण

/**
 * snd_hda_set_घातer_save - reprogram स्वतःsuspend क्रम the given delay
 * @bus: HD-audio bus
 * @delay: स्वतःsuspend delay in msec, 0 = off
 *
 * Synchronize the runसमय PM स्वतःsuspend state from the घातer_save option.
 */
व्योम snd_hda_set_घातer_save(काष्ठा hda_bus *bus, पूर्णांक delay)
अणु
	काष्ठा hda_codec *c;

	list_क्रम_each_codec(c, bus)
		codec_set_घातer_save(c, delay);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_set_घातer_save);

/**
 * snd_hda_check_amp_list_घातer - Check the amp list and update the घातer
 * @codec: HD-audio codec
 * @check: the object containing an AMP list and the status
 * @nid: NID to check / update
 *
 * Check whether the given NID is in the amp list.  If it's in the list,
 * check the current AMP status, and update the घातer-status according
 * to the mute status.
 *
 * This function is supposed to be set or called from the check_घातer_status
 * patch ops.
 */
पूर्णांक snd_hda_check_amp_list_घातer(काष्ठा hda_codec *codec,
				 काष्ठा hda_loopback_check *check,
				 hda_nid_t nid)
अणु
	स्थिर काष्ठा hda_amp_list *p;
	पूर्णांक ch, v;

	अगर (!check->amplist)
		वापस 0;
	क्रम (p = check->amplist; p->nid; p++) अणु
		अगर (p->nid == nid)
			अवरोध;
	पूर्ण
	अगर (!p->nid)
		वापस 0; /* nothing changed */

	क्रम (p = check->amplist; p->nid; p++) अणु
		क्रम (ch = 0; ch < 2; ch++) अणु
			v = snd_hda_codec_amp_पढ़ो(codec, p->nid, ch, p->dir,
						   p->idx);
			अगर (!(v & HDA_AMP_MUTE) && v > 0) अणु
				अगर (!check->घातer_on) अणु
					check->घातer_on = 1;
					snd_hda_घातer_up_pm(codec);
				पूर्ण
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (check->घातer_on) अणु
		check->घातer_on = 0;
		snd_hda_घातer_करोwn_pm(codec);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_check_amp_list_घातer);
#पूर्ण_अगर

/*
 * input MUX helper
 */

/**
 * snd_hda_input_mux_info - Info callback helper क्रम the input-mux क्रमागत
 * @imux: imux helper object
 * @uinfo: poपूर्णांकer to get/store the data
 */
पूर्णांक snd_hda_input_mux_info(स्थिर काष्ठा hda_input_mux *imux,
			   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अचिन्हित पूर्णांक index;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = imux->num_items;
	अगर (!imux->num_items)
		वापस 0;
	index = uinfo->value.क्रमागतerated.item;
	अगर (index >= imux->num_items)
		index = imux->num_items - 1;
	म_नकल(uinfo->value.क्रमागतerated.name, imux->items[index].label);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_input_mux_info);

/**
 * snd_hda_input_mux_put - Put callback helper क्रम the input-mux क्रमागत
 * @codec: the HDA codec
 * @imux: imux helper object
 * @ucontrol: poपूर्णांकer to get/store the data
 * @nid: input mux NID
 * @cur_val: poपूर्णांकer to get/store the current imux value
 */
पूर्णांक snd_hda_input_mux_put(काष्ठा hda_codec *codec,
			  स्थिर काष्ठा hda_input_mux *imux,
			  काष्ठा snd_ctl_elem_value *ucontrol,
			  hda_nid_t nid,
			  अचिन्हित पूर्णांक *cur_val)
अणु
	अचिन्हित पूर्णांक idx;

	अगर (!imux->num_items)
		वापस 0;
	idx = ucontrol->value.क्रमागतerated.item[0];
	अगर (idx >= imux->num_items)
		idx = imux->num_items - 1;
	अगर (*cur_val == idx)
		वापस 0;
	snd_hda_codec_ग_लिखो_cache(codec, nid, 0, AC_VERB_SET_CONNECT_SEL,
				  imux->items[idx].index);
	*cur_val = idx;
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_input_mux_put);


/**
 * snd_hda_क्रमागत_helper_info - Helper क्रम simple क्रमागत ctls
 * @kcontrol: ctl element
 * @uinfo: poपूर्णांकer to get/store the data
 * @num_items: number of क्रमागत items
 * @texts: क्रमागत item string array
 *
 * process kcontrol info callback of a simple string क्रमागत array
 * when @num_items is 0 or @texts is शून्य, assume a boolean क्रमागत array
 */
पूर्णांक snd_hda_क्रमागत_helper_info(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_info *uinfo,
			     पूर्णांक num_items, स्थिर अक्षर * स्थिर *texts)
अणु
	अटल स्थिर अक्षर * स्थिर texts_शेष[] = अणु
		"Disabled", "Enabled"
	पूर्ण;

	अगर (!texts || !num_items) अणु
		num_items = 2;
		texts = texts_शेष;
	पूर्ण

	वापस snd_ctl_क्रमागत_info(uinfo, 1, num_items, texts);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_क्रमागत_helper_info);

/*
 * Multi-channel / digital-out PCM helper functions
 */

/* setup SPDIF output stream */
अटल व्योम setup_dig_out_stream(काष्ठा hda_codec *codec, hda_nid_t nid,
				 अचिन्हित पूर्णांक stream_tag, अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा hda_spdअगर_out *spdअगर;
	अचिन्हित पूर्णांक curr_fmt;
	bool reset;

	spdअगर = snd_hda_spdअगर_out_of_nid(codec, nid);
	/* Add sanity check to pass klockwork check.
	 * This should never happen.
	 */
	अगर (WARN_ON(spdअगर == शून्य))
		वापस;

	curr_fmt = snd_hda_codec_पढ़ो(codec, nid, 0,
				      AC_VERB_GET_STREAM_FORMAT, 0);
	reset = codec->spdअगर_status_reset &&
		(spdअगर->ctls & AC_DIG1_ENABLE) &&
		curr_fmt != क्रमmat;

	/* turn off SPDIF अगर needed; otherwise the IEC958 bits won't be
	   updated */
	अगर (reset)
		set_dig_out_convert(codec, nid,
				    spdअगर->ctls & ~AC_DIG1_ENABLE & 0xff,
				    -1);
	snd_hda_codec_setup_stream(codec, nid, stream_tag, 0, क्रमmat);
	अगर (codec->follower_dig_outs) अणु
		स्थिर hda_nid_t *d;
		क्रम (d = codec->follower_dig_outs; *d; d++)
			snd_hda_codec_setup_stream(codec, *d, stream_tag, 0,
						   क्रमmat);
	पूर्ण
	/* turn on again (अगर needed) */
	अगर (reset)
		set_dig_out_convert(codec, nid,
				    spdअगर->ctls & 0xff, -1);
पूर्ण

अटल व्योम cleanup_dig_out_stream(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	snd_hda_codec_cleanup_stream(codec, nid);
	अगर (codec->follower_dig_outs) अणु
		स्थिर hda_nid_t *d;
		क्रम (d = codec->follower_dig_outs; *d; d++)
			snd_hda_codec_cleanup_stream(codec, *d);
	पूर्ण
पूर्ण

/**
 * snd_hda_multi_out_dig_खोलो - खोलो the digital out in the exclusive mode
 * @codec: the HDA codec
 * @mout: hda_multi_out object
 */
पूर्णांक snd_hda_multi_out_dig_खोलो(काष्ठा hda_codec *codec,
			       काष्ठा hda_multi_out *mout)
अणु
	mutex_lock(&codec->spdअगर_mutex);
	अगर (mout->dig_out_used == HDA_DIG_ANALOG_DUP)
		/* alपढ़ोy खोलोed as analog dup; reset it once */
		cleanup_dig_out_stream(codec, mout->dig_out_nid);
	mout->dig_out_used = HDA_DIG_EXCLUSIVE;
	mutex_unlock(&codec->spdअगर_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_multi_out_dig_खोलो);

/**
 * snd_hda_multi_out_dig_prepare - prepare the digital out stream
 * @codec: the HDA codec
 * @mout: hda_multi_out object
 * @stream_tag: stream tag to assign
 * @क्रमmat: क्रमmat id to assign
 * @substream: PCM substream to assign
 */
पूर्णांक snd_hda_multi_out_dig_prepare(काष्ठा hda_codec *codec,
				  काष्ठा hda_multi_out *mout,
				  अचिन्हित पूर्णांक stream_tag,
				  अचिन्हित पूर्णांक क्रमmat,
				  काष्ठा snd_pcm_substream *substream)
अणु
	mutex_lock(&codec->spdअगर_mutex);
	setup_dig_out_stream(codec, mout->dig_out_nid, stream_tag, क्रमmat);
	mutex_unlock(&codec->spdअगर_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_multi_out_dig_prepare);

/**
 * snd_hda_multi_out_dig_cleanup - clean-up the digital out stream
 * @codec: the HDA codec
 * @mout: hda_multi_out object
 */
पूर्णांक snd_hda_multi_out_dig_cleanup(काष्ठा hda_codec *codec,
				  काष्ठा hda_multi_out *mout)
अणु
	mutex_lock(&codec->spdअगर_mutex);
	cleanup_dig_out_stream(codec, mout->dig_out_nid);
	mutex_unlock(&codec->spdअगर_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_multi_out_dig_cleanup);

/**
 * snd_hda_multi_out_dig_बंद - release the digital out stream
 * @codec: the HDA codec
 * @mout: hda_multi_out object
 */
पूर्णांक snd_hda_multi_out_dig_बंद(काष्ठा hda_codec *codec,
				काष्ठा hda_multi_out *mout)
अणु
	mutex_lock(&codec->spdअगर_mutex);
	mout->dig_out_used = 0;
	mutex_unlock(&codec->spdअगर_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_multi_out_dig_बंद);

/**
 * snd_hda_multi_out_analog_खोलो - खोलो analog outमाला_दो
 * @codec: the HDA codec
 * @mout: hda_multi_out object
 * @substream: PCM substream to assign
 * @hinfo: PCM inक्रमmation to assign
 *
 * Open analog outमाला_दो and set up the hw-स्थिरraपूर्णांकs.
 * If the digital outमाला_दो can be खोलोed as follower, खोलो the digital
 * outमाला_दो, too.
 */
पूर्णांक snd_hda_multi_out_analog_खोलो(काष्ठा hda_codec *codec,
				  काष्ठा hda_multi_out *mout,
				  काष्ठा snd_pcm_substream *substream,
				  काष्ठा hda_pcm_stream *hinfo)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	runसमय->hw.channels_max = mout->max_channels;
	अगर (mout->dig_out_nid) अणु
		अगर (!mout->analog_rates) अणु
			mout->analog_rates = hinfo->rates;
			mout->analog_क्रमmats = hinfo->क्रमmats;
			mout->analog_maxbps = hinfo->maxbps;
		पूर्ण अन्यथा अणु
			runसमय->hw.rates = mout->analog_rates;
			runसमय->hw.क्रमmats = mout->analog_क्रमmats;
			hinfo->maxbps = mout->analog_maxbps;
		पूर्ण
		अगर (!mout->spdअगर_rates) अणु
			snd_hda_query_supported_pcm(codec, mout->dig_out_nid,
						    &mout->spdअगर_rates,
						    &mout->spdअगर_क्रमmats,
						    &mout->spdअगर_maxbps);
		पूर्ण
		mutex_lock(&codec->spdअगर_mutex);
		अगर (mout->share_spdअगर) अणु
			अगर ((runसमय->hw.rates & mout->spdअगर_rates) &&
			    (runसमय->hw.क्रमmats & mout->spdअगर_क्रमmats)) अणु
				runसमय->hw.rates &= mout->spdअगर_rates;
				runसमय->hw.क्रमmats &= mout->spdअगर_क्रमmats;
				अगर (mout->spdअगर_maxbps < hinfo->maxbps)
					hinfo->maxbps = mout->spdअगर_maxbps;
			पूर्ण अन्यथा अणु
				mout->share_spdअगर = 0;
				/* FIXME: need notअगरy? */
			पूर्ण
		पूर्ण
		mutex_unlock(&codec->spdअगर_mutex);
	पूर्ण
	वापस snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_CHANNELS, 2);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_multi_out_analog_खोलो);

/**
 * snd_hda_multi_out_analog_prepare - Preapre the analog outमाला_दो.
 * @codec: the HDA codec
 * @mout: hda_multi_out object
 * @stream_tag: stream tag to assign
 * @क्रमmat: क्रमmat id to assign
 * @substream: PCM substream to assign
 *
 * Set up the i/o क्रम analog out.
 * When the digital out is available, copy the front out to digital out, too.
 */
पूर्णांक snd_hda_multi_out_analog_prepare(काष्ठा hda_codec *codec,
				     काष्ठा hda_multi_out *mout,
				     अचिन्हित पूर्णांक stream_tag,
				     अचिन्हित पूर्णांक क्रमmat,
				     काष्ठा snd_pcm_substream *substream)
अणु
	स्थिर hda_nid_t *nids = mout->dac_nids;
	पूर्णांक chs = substream->runसमय->channels;
	काष्ठा hda_spdअगर_out *spdअगर;
	पूर्णांक i;

	mutex_lock(&codec->spdअगर_mutex);
	spdअगर = snd_hda_spdअगर_out_of_nid(codec, mout->dig_out_nid);
	अगर (mout->dig_out_nid && mout->share_spdअगर &&
	    mout->dig_out_used != HDA_DIG_EXCLUSIVE) अणु
		अगर (chs == 2 && spdअगर != शून्य &&
		    snd_hda_is_supported_क्रमmat(codec, mout->dig_out_nid,
						क्रमmat) &&
		    !(spdअगर->status & IEC958_AES0_NONAUDIO)) अणु
			mout->dig_out_used = HDA_DIG_ANALOG_DUP;
			setup_dig_out_stream(codec, mout->dig_out_nid,
					     stream_tag, क्रमmat);
		पूर्ण अन्यथा अणु
			mout->dig_out_used = 0;
			cleanup_dig_out_stream(codec, mout->dig_out_nid);
		पूर्ण
	पूर्ण
	mutex_unlock(&codec->spdअगर_mutex);

	/* front */
	snd_hda_codec_setup_stream(codec, nids[HDA_FRONT], stream_tag,
				   0, क्रमmat);
	अगर (!mout->no_share_stream &&
	    mout->hp_nid && mout->hp_nid != nids[HDA_FRONT])
		/* headphone out will just decode front left/right (stereo) */
		snd_hda_codec_setup_stream(codec, mout->hp_nid, stream_tag,
					   0, क्रमmat);
	/* extra outमाला_दो copied from front */
	क्रम (i = 0; i < ARRAY_SIZE(mout->hp_out_nid); i++)
		अगर (!mout->no_share_stream && mout->hp_out_nid[i])
			snd_hda_codec_setup_stream(codec,
						   mout->hp_out_nid[i],
						   stream_tag, 0, क्रमmat);

	/* surrounds */
	क्रम (i = 1; i < mout->num_dacs; i++) अणु
		अगर (chs >= (i + 1) * 2) /* independent out */
			snd_hda_codec_setup_stream(codec, nids[i], stream_tag,
						   i * 2, क्रमmat);
		अन्यथा अगर (!mout->no_share_stream) /* copy front */
			snd_hda_codec_setup_stream(codec, nids[i], stream_tag,
						   0, क्रमmat);
	पूर्ण

	/* extra surrounds */
	क्रम (i = 0; i < ARRAY_SIZE(mout->extra_out_nid); i++) अणु
		पूर्णांक ch = 0;
		अगर (!mout->extra_out_nid[i])
			अवरोध;
		अगर (chs >= (i + 1) * 2)
			ch = i * 2;
		अन्यथा अगर (!mout->no_share_stream)
			अवरोध;
		snd_hda_codec_setup_stream(codec, mout->extra_out_nid[i],
					   stream_tag, ch, क्रमmat);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_multi_out_analog_prepare);

/**
 * snd_hda_multi_out_analog_cleanup - clean up the setting क्रम analog out
 * @codec: the HDA codec
 * @mout: hda_multi_out object
 */
पूर्णांक snd_hda_multi_out_analog_cleanup(काष्ठा hda_codec *codec,
				     काष्ठा hda_multi_out *mout)
अणु
	स्थिर hda_nid_t *nids = mout->dac_nids;
	पूर्णांक i;

	क्रम (i = 0; i < mout->num_dacs; i++)
		snd_hda_codec_cleanup_stream(codec, nids[i]);
	अगर (mout->hp_nid)
		snd_hda_codec_cleanup_stream(codec, mout->hp_nid);
	क्रम (i = 0; i < ARRAY_SIZE(mout->hp_out_nid); i++)
		अगर (mout->hp_out_nid[i])
			snd_hda_codec_cleanup_stream(codec,
						     mout->hp_out_nid[i]);
	क्रम (i = 0; i < ARRAY_SIZE(mout->extra_out_nid); i++)
		अगर (mout->extra_out_nid[i])
			snd_hda_codec_cleanup_stream(codec,
						     mout->extra_out_nid[i]);
	mutex_lock(&codec->spdअगर_mutex);
	अगर (mout->dig_out_nid && mout->dig_out_used == HDA_DIG_ANALOG_DUP) अणु
		cleanup_dig_out_stream(codec, mout->dig_out_nid);
		mout->dig_out_used = 0;
	पूर्ण
	mutex_unlock(&codec->spdअगर_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_multi_out_analog_cleanup);

/**
 * snd_hda_get_शेष_vref - Get the शेष (mic) VREF pin bits
 * @codec: the HDA codec
 * @pin: referred pin NID
 *
 * Guess the suitable VREF pin bits to be set as the pin-control value.
 * Note: the function करोesn't set the AC_PINCTL_IN_EN bit.
 */
अचिन्हित पूर्णांक snd_hda_get_शेष_vref(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	अचिन्हित पूर्णांक pincap;
	अचिन्हित पूर्णांक oldval;
	oldval = snd_hda_codec_पढ़ो(codec, pin, 0,
				    AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
	pincap = snd_hda_query_pin_caps(codec, pin);
	pincap = (pincap & AC_PINCAP_VREF) >> AC_PINCAP_VREF_SHIFT;
	/* Exception: अगर the शेष pin setup is vref50, we give it priority */
	अगर ((pincap & AC_PINCAP_VREF_80) && oldval != PIN_VREF50)
		वापस AC_PINCTL_VREF_80;
	अन्यथा अगर (pincap & AC_PINCAP_VREF_50)
		वापस AC_PINCTL_VREF_50;
	अन्यथा अगर (pincap & AC_PINCAP_VREF_100)
		वापस AC_PINCTL_VREF_100;
	अन्यथा अगर (pincap & AC_PINCAP_VREF_GRD)
		वापस AC_PINCTL_VREF_GRD;
	वापस AC_PINCTL_VREF_HIZ;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_शेष_vref);

/**
 * snd_hda_correct_pin_ctl - correct the pin ctl value क्रम matching with the pin cap
 * @codec: the HDA codec
 * @pin: referred pin NID
 * @val: pin ctl value to audit
 */
अचिन्हित पूर्णांक snd_hda_correct_pin_ctl(काष्ठा hda_codec *codec,
				     hda_nid_t pin, अचिन्हित पूर्णांक val)
अणु
	अटल स्थिर अचिन्हित पूर्णांक cap_lists[][2] = अणु
		अणु AC_PINCTL_VREF_100, AC_PINCAP_VREF_100 पूर्ण,
		अणु AC_PINCTL_VREF_80, AC_PINCAP_VREF_80 पूर्ण,
		अणु AC_PINCTL_VREF_50, AC_PINCAP_VREF_50 पूर्ण,
		अणु AC_PINCTL_VREF_GRD, AC_PINCAP_VREF_GRD पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक cap;

	अगर (!val)
		वापस 0;
	cap = snd_hda_query_pin_caps(codec, pin);
	अगर (!cap)
		वापस val; /* करोn't know what to करो... */

	अगर (val & AC_PINCTL_OUT_EN) अणु
		अगर (!(cap & AC_PINCAP_OUT))
			val &= ~(AC_PINCTL_OUT_EN | AC_PINCTL_HP_EN);
		अन्यथा अगर ((val & AC_PINCTL_HP_EN) && !(cap & AC_PINCAP_HP_DRV))
			val &= ~AC_PINCTL_HP_EN;
	पूर्ण

	अगर (val & AC_PINCTL_IN_EN) अणु
		अगर (!(cap & AC_PINCAP_IN))
			val &= ~(AC_PINCTL_IN_EN | AC_PINCTL_VREFEN);
		अन्यथा अणु
			अचिन्हित पूर्णांक vcap, vref;
			पूर्णांक i;
			vcap = (cap & AC_PINCAP_VREF) >> AC_PINCAP_VREF_SHIFT;
			vref = val & AC_PINCTL_VREFEN;
			क्रम (i = 0; i < ARRAY_SIZE(cap_lists); i++) अणु
				अगर (vref == cap_lists[i][0] &&
				    !(vcap & cap_lists[i][1])) अणु
					अगर (i == ARRAY_SIZE(cap_lists) - 1)
						vref = AC_PINCTL_VREF_HIZ;
					अन्यथा
						vref = cap_lists[i + 1][0];
				पूर्ण
			पूर्ण
			val &= ~AC_PINCTL_VREFEN;
			val |= vref;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_correct_pin_ctl);

/**
 * _snd_hda_set_pin_ctl - Helper to set pin ctl value
 * @codec: the HDA codec
 * @pin: referred pin NID
 * @val: pin control value to set
 * @cached: access over codec pinctl cache or direct ग_लिखो
 *
 * This function is a helper to set a pin ctl value more safely.
 * It corrects the pin ctl value via snd_hda_correct_pin_ctl(), stores the
 * value in pin target array via snd_hda_codec_set_pin_target(), then
 * actually ग_लिखोs the value via either snd_hda_codec_ग_लिखो_cache() or
 * snd_hda_codec_ग_लिखो() depending on @cached flag.
 */
पूर्णांक _snd_hda_set_pin_ctl(काष्ठा hda_codec *codec, hda_nid_t pin,
			 अचिन्हित पूर्णांक val, bool cached)
अणु
	val = snd_hda_correct_pin_ctl(codec, pin, val);
	snd_hda_codec_set_pin_target(codec, pin, val);
	अगर (cached)
		वापस snd_hda_codec_ग_लिखो_cache(codec, pin, 0,
				AC_VERB_SET_PIN_WIDGET_CONTROL, val);
	अन्यथा
		वापस snd_hda_codec_ग_लिखो(codec, pin, 0,
					   AC_VERB_SET_PIN_WIDGET_CONTROL, val);
पूर्ण
EXPORT_SYMBOL_GPL(_snd_hda_set_pin_ctl);

/**
 * snd_hda_add_imux_item - Add an item to input_mux
 * @codec: the HDA codec
 * @imux: imux helper object
 * @label: the name of imux item to assign
 * @index: index number of imux item to assign
 * @type_idx: poपूर्णांकer to store the resultant label index
 *
 * When the same label is used alपढ़ोy in the existing items, the number
 * suffix is appended to the label.  This label index number is stored
 * to type_idx when non-शून्य poपूर्णांकer is given.
 */
पूर्णांक snd_hda_add_imux_item(काष्ठा hda_codec *codec,
			  काष्ठा hda_input_mux *imux, स्थिर अक्षर *label,
			  पूर्णांक index, पूर्णांक *type_idx)
अणु
	पूर्णांक i, label_idx = 0;
	अगर (imux->num_items >= HDA_MAX_NUM_INPUTS) अणु
		codec_err(codec, "hda_codec: Too many imux items!\n");
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < imux->num_items; i++) अणु
		अगर (!म_भेदन(label, imux->items[i].label, म_माप(label)))
			label_idx++;
	पूर्ण
	अगर (type_idx)
		*type_idx = label_idx;
	अगर (label_idx > 0)
		snम_लिखो(imux->items[imux->num_items].label,
			 माप(imux->items[imux->num_items].label),
			 "%s %d", label, label_idx);
	अन्यथा
		strscpy(imux->items[imux->num_items].label, label,
			माप(imux->items[imux->num_items].label));
	imux->items[imux->num_items].index = index;
	imux->num_items++;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_add_imux_item);

/**
 * snd_hda_bus_reset_codecs - Reset the bus
 * @bus: HD-audio bus
 */
व्योम snd_hda_bus_reset_codecs(काष्ठा hda_bus *bus)
अणु
	काष्ठा hda_codec *codec;

	list_क्रम_each_codec(codec, bus) अणु
		/* FIXME: maybe a better way needed क्रम क्रमced reset */
		अगर (current_work() != &codec->jackpoll_work.work)
			cancel_delayed_work_sync(&codec->jackpoll_work);
#अगर_घोषित CONFIG_PM
		अगर (hda_codec_is_घातer_on(codec)) अणु
			hda_call_codec_suspend(codec);
			hda_call_codec_resume(codec);
		पूर्ण
#पूर्ण_अगर
	पूर्ण
पूर्ण

/**
 * snd_prपूर्णांक_pcm_bits - Prपूर्णांक the supported PCM fmt bits to the string buffer
 * @pcm: PCM caps bits
 * @buf: the string buffer to ग_लिखो
 * @buflen: the max buffer length
 *
 * used by hda_proc.c and hda_eld.c
 */
व्योम snd_prपूर्णांक_pcm_bits(पूर्णांक pcm, अक्षर *buf, पूर्णांक buflen)
अणु
	अटल स्थिर अचिन्हित पूर्णांक bits[] = अणु 8, 16, 20, 24, 32 पूर्ण;
	पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < ARRAY_SIZE(bits); i++)
		अगर (pcm & (AC_SUPPCM_BITS_8 << i))
			j += scnम_लिखो(buf + j, buflen - j,  " %d", bits[i]);

	buf[j] = '\0'; /* necessary when j == 0 */
पूर्ण
EXPORT_SYMBOL_GPL(snd_prपूर्णांक_pcm_bits);

MODULE_DESCRIPTION("HDA codec core");
MODULE_LICENSE("GPL");
