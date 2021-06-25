<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HD-audio codec core device
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/hdaudपन.स>
#समावेश <sound/hda_regmap.h>
#समावेश <sound/pcm.h>
#समावेश "local.h"

अटल व्योम setup_fg_nodes(काष्ठा hdac_device *codec);
अटल पूर्णांक get_codec_venकरोr_name(काष्ठा hdac_device *codec);

अटल व्योम शेष_release(काष्ठा device *dev)
अणु
	snd_hdac_device_निकास(dev_to_hdac_dev(dev));
पूर्ण

/**
 * snd_hdac_device_init - initialize the HD-audio codec base device
 * @codec: device to initialize
 * @bus: but to attach
 * @name: device name string
 * @addr: codec address
 *
 * Returns zero क्रम success or a negative error code.
 *
 * This function increments the runसमय PM counter and marks it active.
 * The caller needs to turn it off appropriately later.
 *
 * The caller needs to set the device's release op properly by itself.
 */
पूर्णांक snd_hdac_device_init(काष्ठा hdac_device *codec, काष्ठा hdac_bus *bus,
			 स्थिर अक्षर *name, अचिन्हित पूर्णांक addr)
अणु
	काष्ठा device *dev;
	hda_nid_t fg;
	पूर्णांक err;

	dev = &codec->dev;
	device_initialize(dev);
	dev->parent = bus->dev;
	dev->bus = &snd_hda_bus_type;
	dev->release = शेष_release;
	dev->groups = hdac_dev_attr_groups;
	dev_set_name(dev, "%s", name);
	device_enable_async_suspend(dev);

	codec->bus = bus;
	codec->addr = addr;
	codec->type = HDA_DEV_CORE;
	mutex_init(&codec->widget_lock);
	mutex_init(&codec->regmap_lock);
	pm_runसमय_set_active(&codec->dev);
	pm_runसमय_get_noresume(&codec->dev);
	atomic_set(&codec->in_pm, 0);

	err = snd_hdac_bus_add_device(bus, codec);
	अगर (err < 0)
		जाओ error;

	/* fill parameters */
	codec->venकरोr_id = snd_hdac_पढ़ो_parm(codec, AC_NODE_ROOT,
					      AC_PAR_VENDOR_ID);
	अगर (codec->venकरोr_id == -1) अणु
		/* पढ़ो again, hopefully the access method was corrected
		 * in the last पढ़ो...
		 */
		codec->venकरोr_id = snd_hdac_पढ़ो_parm(codec, AC_NODE_ROOT,
						      AC_PAR_VENDOR_ID);
	पूर्ण

	codec->subप्रणाली_id = snd_hdac_पढ़ो_parm(codec, AC_NODE_ROOT,
						 AC_PAR_SUBSYSTEM_ID);
	codec->revision_id = snd_hdac_पढ़ो_parm(codec, AC_NODE_ROOT,
						AC_PAR_REV_ID);

	setup_fg_nodes(codec);
	अगर (!codec->afg && !codec->mfg) अणु
		dev_err(dev, "no AFG or MFG node found\n");
		err = -ENODEV;
		जाओ error;
	पूर्ण

	fg = codec->afg ? codec->afg : codec->mfg;

	err = snd_hdac_refresh_widमाला_लो(codec);
	अगर (err < 0)
		जाओ error;

	codec->घातer_caps = snd_hdac_पढ़ो_parm(codec, fg, AC_PAR_POWER_STATE);
	/* reपढ़ो ssid अगर not set by parameter */
	अगर (codec->subप्रणाली_id == -1 || codec->subप्रणाली_id == 0)
		snd_hdac_पढ़ो(codec, fg, AC_VERB_GET_SUBSYSTEM_ID, 0,
			      &codec->subप्रणाली_id);

	err = get_codec_venकरोr_name(codec);
	अगर (err < 0)
		जाओ error;

	codec->chip_name = kaप्र_लिखो(GFP_KERNEL, "ID %x",
				     codec->venकरोr_id & 0xffff);
	अगर (!codec->chip_name) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	वापस 0;

 error:
	put_device(&codec->dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_device_init);

/**
 * snd_hdac_device_निकास - clean up the HD-audio codec base device
 * @codec: device to clean up
 */
व्योम snd_hdac_device_निकास(काष्ठा hdac_device *codec)
अणु
	pm_runसमय_put_noidle(&codec->dev);
	/* keep balance of runसमय PM child_count in parent device */
	pm_runसमय_set_suspended(&codec->dev);
	snd_hdac_bus_हटाओ_device(codec->bus, codec);
	kमुक्त(codec->venकरोr_name);
	kमुक्त(codec->chip_name);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_device_निकास);

/**
 * snd_hdac_device_रेजिस्टर - रेजिस्टर the hd-audio codec base device
 * @codec: the device to रेजिस्टर
 */
पूर्णांक snd_hdac_device_रेजिस्टर(काष्ठा hdac_device *codec)
अणु
	पूर्णांक err;

	err = device_add(&codec->dev);
	अगर (err < 0)
		वापस err;
	mutex_lock(&codec->widget_lock);
	err = hda_widget_sysfs_init(codec);
	mutex_unlock(&codec->widget_lock);
	अगर (err < 0) अणु
		device_del(&codec->dev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_device_रेजिस्टर);

/**
 * snd_hdac_device_unरेजिस्टर - unरेजिस्टर the hd-audio codec base device
 * @codec: the device to unरेजिस्टर
 */
व्योम snd_hdac_device_unरेजिस्टर(काष्ठा hdac_device *codec)
अणु
	अगर (device_is_रेजिस्टरed(&codec->dev)) अणु
		mutex_lock(&codec->widget_lock);
		hda_widget_sysfs_निकास(codec);
		mutex_unlock(&codec->widget_lock);
		device_del(&codec->dev);
		snd_hdac_bus_हटाओ_device(codec->bus, codec);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_device_unरेजिस्टर);

/**
 * snd_hdac_device_set_chip_name - set/update the codec name
 * @codec: the HDAC device
 * @name: name string to set
 *
 * Returns 0 अगर the name is set or updated, or a negative error code.
 */
पूर्णांक snd_hdac_device_set_chip_name(काष्ठा hdac_device *codec, स्थिर अक्षर *name)
अणु
	अक्षर *newname;

	अगर (!name)
		वापस 0;
	newname = kstrdup(name, GFP_KERNEL);
	अगर (!newname)
		वापस -ENOMEM;
	kमुक्त(codec->chip_name);
	codec->chip_name = newname;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_device_set_chip_name);

/**
 * snd_hdac_codec_modalias - give the module alias name
 * @codec: HDAC device
 * @buf: string buffer to store
 * @size: string buffer size
 *
 * Returns the size of string, like snम_लिखो(), or a negative error code.
 */
पूर्णांक snd_hdac_codec_modalias(काष्ठा hdac_device *codec, अक्षर *buf, माप_प्रकार size)
अणु
	वापस scnम_लिखो(buf, size, "hdaudio:v%08Xr%08Xa%02X\n",
			codec->venकरोr_id, codec->revision_id, codec->type);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_codec_modalias);

/**
 * snd_hdac_make_cmd - compose a 32bit command word to be sent to the
 *	HD-audio controller
 * @codec: the codec object
 * @nid: NID to encode
 * @verb: verb to encode
 * @parm: parameter to encode
 *
 * Return an encoded command verb or -1 क्रम error.
 */
अटल अचिन्हित पूर्णांक snd_hdac_make_cmd(काष्ठा hdac_device *codec, hda_nid_t nid,
				      अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm)
अणु
	u32 val, addr;

	addr = codec->addr;
	अगर ((addr & ~0xf) || (nid & ~0x7f) ||
	    (verb & ~0xfff) || (parm & ~0xffff)) अणु
		dev_err(&codec->dev, "out of range cmd %x:%x:%x:%x\n",
			addr, nid, verb, parm);
		वापस -1;
	पूर्ण

	val = addr << 28;
	val |= (u32)nid << 20;
	val |= verb << 8;
	val |= parm;
	वापस val;
पूर्ण

/**
 * snd_hdac_exec_verb - execute an encoded verb
 * @codec: the codec object
 * @cmd: encoded verb to execute
 * @flags: optional flags, pass zero क्रम शेष
 * @res: the poपूर्णांकer to store the result, शून्य अगर running async
 *
 * Returns zero अगर successful, or a negative error code.
 *
 * This calls the exec_verb op when set in hdac_codec.  If not,
 * call the शेष snd_hdac_bus_exec_verb().
 */
पूर्णांक snd_hdac_exec_verb(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक cmd,
		       अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक *res)
अणु
	अगर (codec->exec_verb)
		वापस codec->exec_verb(codec, cmd, flags, res);
	वापस snd_hdac_bus_exec_verb(codec->bus, codec->addr, cmd, res);
पूर्ण


/**
 * snd_hdac_पढ़ो - execute a verb
 * @codec: the codec object
 * @nid: NID to execute a verb
 * @verb: verb to execute
 * @parm: parameter क्रम a verb
 * @res: the poपूर्णांकer to store the result, शून्य अगर running async
 *
 * Returns zero अगर successful, or a negative error code.
 */
पूर्णांक snd_hdac_पढ़ो(काष्ठा hdac_device *codec, hda_nid_t nid,
		  अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm, अचिन्हित पूर्णांक *res)
अणु
	अचिन्हित पूर्णांक cmd = snd_hdac_make_cmd(codec, nid, verb, parm);

	वापस snd_hdac_exec_verb(codec, cmd, 0, res);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_पढ़ो);

/**
 * _snd_hdac_पढ़ो_parm - पढ़ो a parmeter
 * @codec: the codec object
 * @nid: NID to पढ़ो a parameter
 * @parm: parameter to पढ़ो
 * @res: poपूर्णांकer to store the पढ़ो value
 *
 * This function वापसs zero or an error unlike snd_hdac_पढ़ो_parm().
 */
पूर्णांक _snd_hdac_पढ़ो_parm(काष्ठा hdac_device *codec, hda_nid_t nid, पूर्णांक parm,
			अचिन्हित पूर्णांक *res)
अणु
	अचिन्हित पूर्णांक cmd;

	cmd = snd_hdac_regmap_encode_verb(nid, AC_VERB_PARAMETERS) | parm;
	वापस snd_hdac_regmap_पढ़ो_raw(codec, cmd, res);
पूर्ण
EXPORT_SYMBOL_GPL(_snd_hdac_पढ़ो_parm);

/**
 * snd_hdac_पढ़ो_parm_uncached - पढ़ो a codec parameter without caching
 * @codec: the codec object
 * @nid: NID to पढ़ो a parameter
 * @parm: parameter to पढ़ो
 *
 * Returns -1 क्रम error.  If you need to distinguish the error more
 * strictly, use snd_hdac_पढ़ो() directly.
 */
पूर्णांक snd_hdac_पढ़ो_parm_uncached(काष्ठा hdac_device *codec, hda_nid_t nid,
				पूर्णांक parm)
अणु
	अचिन्हित पूर्णांक cmd, val;

	cmd = snd_hdac_regmap_encode_verb(nid, AC_VERB_PARAMETERS) | parm;
	अगर (snd_hdac_regmap_पढ़ो_raw_uncached(codec, cmd, &val) < 0)
		वापस -1;
	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_पढ़ो_parm_uncached);

/**
 * snd_hdac_override_parm - override पढ़ो-only parameters
 * @codec: the codec object
 * @nid: NID क्रम the parameter
 * @parm: the parameter to change
 * @val: the parameter value to overग_लिखो
 */
पूर्णांक snd_hdac_override_parm(काष्ठा hdac_device *codec, hda_nid_t nid,
			   अचिन्हित पूर्णांक parm, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक verb = (AC_VERB_PARAMETERS << 8) | (nid << 20) | parm;
	पूर्णांक err;

	अगर (!codec->regmap)
		वापस -EINVAL;

	codec->caps_overwriting = true;
	err = snd_hdac_regmap_ग_लिखो_raw(codec, verb, val);
	codec->caps_overwriting = false;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_override_parm);

/**
 * snd_hdac_get_sub_nodes - get start NID and number of subtree nodes
 * @codec: the codec object
 * @nid: NID to inspect
 * @start_id: the poपूर्णांकer to store the starting NID
 *
 * Returns the number of subtree nodes or zero अगर not found.
 * This function पढ़ोs parameters always without caching.
 */
पूर्णांक snd_hdac_get_sub_nodes(काष्ठा hdac_device *codec, hda_nid_t nid,
			   hda_nid_t *start_id)
अणु
	अचिन्हित पूर्णांक parm;

	parm = snd_hdac_पढ़ो_parm_uncached(codec, nid, AC_PAR_NODE_COUNT);
	अगर (parm == -1) अणु
		*start_id = 0;
		वापस 0;
	पूर्ण
	*start_id = (parm >> 16) & 0x7fff;
	वापस (पूर्णांक)(parm & 0x7fff);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_get_sub_nodes);

/*
 * look क्रम an AFG and MFG nodes
 */
अटल व्योम setup_fg_nodes(काष्ठा hdac_device *codec)
अणु
	पूर्णांक i, total_nodes, function_id;
	hda_nid_t nid;

	total_nodes = snd_hdac_get_sub_nodes(codec, AC_NODE_ROOT, &nid);
	क्रम (i = 0; i < total_nodes; i++, nid++) अणु
		function_id = snd_hdac_पढ़ो_parm(codec, nid,
						 AC_PAR_FUNCTION_TYPE);
		चयन (function_id & 0xff) अणु
		हाल AC_GRP_AUDIO_FUNCTION:
			codec->afg = nid;
			codec->afg_function_id = function_id & 0xff;
			codec->afg_unsol = (function_id >> 8) & 1;
			अवरोध;
		हाल AC_GRP_MODEM_FUNCTION:
			codec->mfg = nid;
			codec->mfg_function_id = function_id & 0xff;
			codec->mfg_unsol = (function_id >> 8) & 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * snd_hdac_refresh_widमाला_लो - Reset the widget start/end nodes
 * @codec: the codec object
 */
पूर्णांक snd_hdac_refresh_widमाला_लो(काष्ठा hdac_device *codec)
अणु
	hda_nid_t start_nid;
	पूर्णांक nums, err = 0;

	/*
	 * Serialize against multiple thपढ़ोs trying to update the sysfs
	 * widमाला_लो array.
	 */
	mutex_lock(&codec->widget_lock);
	nums = snd_hdac_get_sub_nodes(codec, codec->afg, &start_nid);
	अगर (!start_nid || nums <= 0 || nums >= 0xff) अणु
		dev_err(&codec->dev, "cannot read sub nodes for FG 0x%02x\n",
			codec->afg);
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	err = hda_widget_sysfs_reinit(codec, start_nid, nums);
	अगर (err < 0)
		जाओ unlock;

	codec->num_nodes = nums;
	codec->start_nid = start_nid;
	codec->end_nid = start_nid + nums;
unlock:
	mutex_unlock(&codec->widget_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_refresh_widमाला_लो);

/* वापस CONNLIST_LEN parameter of the given widget */
अटल अचिन्हित पूर्णांक get_num_conns(काष्ठा hdac_device *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक wcaps = get_wcaps(codec, nid);
	अचिन्हित पूर्णांक parm;

	अगर (!(wcaps & AC_WCAP_CONN_LIST) &&
	    get_wcaps_type(wcaps) != AC_WID_VOL_KNB)
		वापस 0;

	parm = snd_hdac_पढ़ो_parm(codec, nid, AC_PAR_CONNLIST_LEN);
	अगर (parm == -1)
		parm = 0;
	वापस parm;
पूर्ण

/**
 * snd_hdac_get_connections - get a widget connection list
 * @codec: the codec object
 * @nid: NID
 * @conn_list: the array to store the results, can be शून्य
 * @max_conns: the max size of the given array
 *
 * Returns the number of connected widमाला_लो, zero क्रम no connection, or a
 * negative error code.  When the number of elements करोn't fit with the
 * given array size, it वापसs -ENOSPC.
 *
 * When @conn_list is शून्य, it just checks the number of connections.
 */
पूर्णांक snd_hdac_get_connections(काष्ठा hdac_device *codec, hda_nid_t nid,
			     hda_nid_t *conn_list, पूर्णांक max_conns)
अणु
	अचिन्हित पूर्णांक parm;
	पूर्णांक i, conn_len, conns, err;
	अचिन्हित पूर्णांक shअगरt, num_elems, mask;
	hda_nid_t prev_nid;
	पूर्णांक null_count = 0;

	parm = get_num_conns(codec, nid);
	अगर (!parm)
		वापस 0;

	अगर (parm & AC_CLIST_LONG) अणु
		/* दीर्घ क्रमm */
		shअगरt = 16;
		num_elems = 2;
	पूर्ण अन्यथा अणु
		/* लघु क्रमm */
		shअगरt = 8;
		num_elems = 4;
	पूर्ण
	conn_len = parm & AC_CLIST_LENGTH;
	mask = (1 << (shअगरt-1)) - 1;

	अगर (!conn_len)
		वापस 0; /* no connection */

	अगर (conn_len == 1) अणु
		/* single connection */
		err = snd_hdac_पढ़ो(codec, nid, AC_VERB_GET_CONNECT_LIST, 0,
				    &parm);
		अगर (err < 0)
			वापस err;
		अगर (conn_list)
			conn_list[0] = parm & mask;
		वापस 1;
	पूर्ण

	/* multi connection */
	conns = 0;
	prev_nid = 0;
	क्रम (i = 0; i < conn_len; i++) अणु
		पूर्णांक range_val;
		hda_nid_t val, n;

		अगर (i % num_elems == 0) अणु
			err = snd_hdac_पढ़ो(codec, nid,
					    AC_VERB_GET_CONNECT_LIST, i,
					    &parm);
			अगर (err < 0)
				वापस -EIO;
		पूर्ण
		range_val = !!(parm & (1 << (shअगरt-1))); /* ranges */
		val = parm & mask;
		अगर (val == 0 && null_count++) अणु  /* no second chance */
			dev_dbg(&codec->dev,
				"invalid CONNECT_LIST verb %x[%i]:%x\n",
				nid, i, parm);
			वापस 0;
		पूर्ण
		parm >>= shअगरt;
		अगर (range_val) अणु
			/* ranges between the previous and this one */
			अगर (!prev_nid || prev_nid >= val) अणु
				dev_warn(&codec->dev,
					 "invalid dep_range_val %x:%x\n",
					 prev_nid, val);
				जारी;
			पूर्ण
			क्रम (n = prev_nid + 1; n <= val; n++) अणु
				अगर (conn_list) अणु
					अगर (conns >= max_conns)
						वापस -ENOSPC;
					conn_list[conns] = n;
				पूर्ण
				conns++;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (conn_list) अणु
				अगर (conns >= max_conns)
					वापस -ENOSPC;
				conn_list[conns] = val;
			पूर्ण
			conns++;
		पूर्ण
		prev_nid = val;
	पूर्ण
	वापस conns;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_get_connections);

#अगर_घोषित CONFIG_PM
/**
 * snd_hdac_घातer_up - घातer up the codec
 * @codec: the codec object
 *
 * This function calls the runसमय PM helper to घातer up the given codec.
 * Unlike snd_hdac_घातer_up_pm(), you should call this only क्रम the code
 * path that isn't included in PM path.  Otherwise it माला_लो stuck.
 *
 * Returns zero अगर successful, or a negative error code.
 */
पूर्णांक snd_hdac_घातer_up(काष्ठा hdac_device *codec)
अणु
	वापस pm_runसमय_get_sync(&codec->dev);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_घातer_up);

/**
 * snd_hdac_घातer_करोwn - घातer करोwn the codec
 * @codec: the codec object
 *
 * Returns zero अगर successful, or a negative error code.
 */
पूर्णांक snd_hdac_घातer_करोwn(काष्ठा hdac_device *codec)
अणु
	काष्ठा device *dev = &codec->dev;

	pm_runसमय_mark_last_busy(dev);
	वापस pm_runसमय_put_स्वतःsuspend(dev);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_घातer_करोwn);

/**
 * snd_hdac_घातer_up_pm - घातer up the codec
 * @codec: the codec object
 *
 * This function can be called in a recursive code path like init code
 * which may be called by PM suspend/resume again.  OTOH, अगर a घातer-up
 * call must wake up the sleeper (e.g. in a kctl callback), use
 * snd_hdac_घातer_up() instead.
 *
 * Returns zero अगर successful, or a negative error code.
 */
पूर्णांक snd_hdac_घातer_up_pm(काष्ठा hdac_device *codec)
अणु
	अगर (!atomic_inc_not_zero(&codec->in_pm))
		वापस snd_hdac_घातer_up(codec);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_घातer_up_pm);

/* like snd_hdac_घातer_up_pm(), but only increment the pm count when
 * alपढ़ोy घातered up.  Returns -1 अगर not घातered up, 1 अगर incremented
 * or 0 अगर unchanged.  Only used in hdac_regmap.c
 */
पूर्णांक snd_hdac_keep_घातer_up(काष्ठा hdac_device *codec)
अणु
	अगर (!atomic_inc_not_zero(&codec->in_pm)) अणु
		पूर्णांक ret = pm_runसमय_get_अगर_in_use(&codec->dev);
		अगर (!ret)
			वापस -1;
		अगर (ret < 0)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/**
 * snd_hdac_घातer_करोwn_pm - घातer करोwn the codec
 * @codec: the codec object
 *
 * Like snd_hdac_घातer_up_pm(), this function is used in a recursive
 * code path like init code which may be called by PM suspend/resume again.
 *
 * Returns zero अगर successful, or a negative error code.
 */
पूर्णांक snd_hdac_घातer_करोwn_pm(काष्ठा hdac_device *codec)
अणु
	अगर (atomic_dec_अगर_positive(&codec->in_pm) < 0)
		वापस snd_hdac_घातer_करोwn(codec);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_घातer_करोwn_pm);
#पूर्ण_अगर

/* codec venकरोr labels */
काष्ठा hda_venकरोr_id अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा hda_venकरोr_id hda_venकरोr_ids[] = अणु
	अणु 0x1002, "ATI" पूर्ण,
	अणु 0x1013, "Cirrus Logic" पूर्ण,
	अणु 0x1057, "Motorola" पूर्ण,
	अणु 0x1095, "Silicon Image" पूर्ण,
	अणु 0x10de, "Nvidia" पूर्ण,
	अणु 0x10ec, "Realtek" पूर्ण,
	अणु 0x1102, "Creative" पूर्ण,
	अणु 0x1106, "VIA" पूर्ण,
	अणु 0x111d, "IDT" पूर्ण,
	अणु 0x11c1, "LSI" पूर्ण,
	अणु 0x11d4, "Analog Devices" पूर्ण,
	अणु 0x13f6, "C-Media" पूर्ण,
	अणु 0x14f1, "Conexant" पूर्ण,
	अणु 0x17e8, "Chrontel" पूर्ण,
	अणु 0x1854, "LG" पूर्ण,
	अणु 0x1aec, "Wolfson Microelectronics" पूर्ण,
	अणु 0x1af4, "QEMU" पूर्ण,
	अणु 0x434d, "C-Media" पूर्ण,
	अणु 0x8086, "Intel" पूर्ण,
	अणु 0x8384, "SigmaTel" पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

/* store the codec venकरोr name */
अटल पूर्णांक get_codec_venकरोr_name(काष्ठा hdac_device *codec)
अणु
	स्थिर काष्ठा hda_venकरोr_id *c;
	u16 venकरोr_id = codec->venकरोr_id >> 16;

	क्रम (c = hda_venकरोr_ids; c->id; c++) अणु
		अगर (c->id == venकरोr_id) अणु
			codec->venकरोr_name = kstrdup(c->name, GFP_KERNEL);
			वापस codec->venकरोr_name ? 0 : -ENOMEM;
		पूर्ण
	पूर्ण

	codec->venकरोr_name = kaप्र_लिखो(GFP_KERNEL, "Generic %04x", venकरोr_id);
	वापस codec->venकरोr_name ? 0 : -ENOMEM;
पूर्ण

/*
 * stream क्रमmats
 */
काष्ठा hda_rate_tbl अणु
	अचिन्हित पूर्णांक hz;
	अचिन्हित पूर्णांक alsa_bits;
	अचिन्हित पूर्णांक hda_fmt;
पूर्ण;

/* rate = base * mult / भाग */
#घोषणा HDA_RATE(base, mult, भाग) \
	(AC_FMT_BASE_##base##K | (((mult) - 1) << AC_FMT_MULT_SHIFT) | \
	 (((भाग) - 1) << AC_FMT_DIV_SHIFT))

अटल स्थिर काष्ठा hda_rate_tbl rate_bits[] = अणु
	/* rate in Hz, ALSA rate biपंचांगask, HDA क्रमmat value */

	/* स्वतःdetected value used in snd_hda_query_supported_pcm */
	अणु 8000, SNDRV_PCM_RATE_8000, HDA_RATE(48, 1, 6) पूर्ण,
	अणु 11025, SNDRV_PCM_RATE_11025, HDA_RATE(44, 1, 4) पूर्ण,
	अणु 16000, SNDRV_PCM_RATE_16000, HDA_RATE(48, 1, 3) पूर्ण,
	अणु 22050, SNDRV_PCM_RATE_22050, HDA_RATE(44, 1, 2) पूर्ण,
	अणु 32000, SNDRV_PCM_RATE_32000, HDA_RATE(48, 2, 3) पूर्ण,
	अणु 44100, SNDRV_PCM_RATE_44100, HDA_RATE(44, 1, 1) पूर्ण,
	अणु 48000, SNDRV_PCM_RATE_48000, HDA_RATE(48, 1, 1) पूर्ण,
	अणु 88200, SNDRV_PCM_RATE_88200, HDA_RATE(44, 2, 1) पूर्ण,
	अणु 96000, SNDRV_PCM_RATE_96000, HDA_RATE(48, 2, 1) पूर्ण,
	अणु 176400, SNDRV_PCM_RATE_176400, HDA_RATE(44, 4, 1) पूर्ण,
	अणु 192000, SNDRV_PCM_RATE_192000, HDA_RATE(48, 4, 1) पूर्ण,
#घोषणा AC_PAR_PCM_RATE_BITS	11
	/* up to bits 10, 384kHZ isn't supported properly */

	/* not स्वतःdetected value */
	अणु 9600, SNDRV_PCM_RATE_KNOT, HDA_RATE(48, 1, 5) पूर्ण,

	अणु 0 पूर्ण /* terminator */
पूर्ण;

/**
 * snd_hdac_calc_stream_क्रमmat - calculate the क्रमmat bitset
 * @rate: the sample rate
 * @channels: the number of channels
 * @क्रमmat: the PCM क्रमmat (SNDRV_PCM_FORMAT_XXX)
 * @maxbps: the max. bps
 * @spdअगर_ctls: HD-audio SPDIF status bits (0 अगर irrelevant)
 *
 * Calculate the क्रमmat bitset from the given rate, channels and th PCM क्रमmat.
 *
 * Return zero अगर invalid.
 */
अचिन्हित पूर्णांक snd_hdac_calc_stream_क्रमmat(अचिन्हित पूर्णांक rate,
					 अचिन्हित पूर्णांक channels,
					 snd_pcm_क्रमmat_t क्रमmat,
					 अचिन्हित पूर्णांक maxbps,
					 अचिन्हित लघु spdअगर_ctls)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक val = 0;

	क्रम (i = 0; rate_bits[i].hz; i++)
		अगर (rate_bits[i].hz == rate) अणु
			val = rate_bits[i].hda_fmt;
			अवरोध;
		पूर्ण
	अगर (!rate_bits[i].hz)
		वापस 0;

	अगर (channels == 0 || channels > 8)
		वापस 0;
	val |= channels - 1;

	चयन (snd_pcm_क्रमmat_width(क्रमmat)) अणु
	हाल 8:
		val |= AC_FMT_BITS_8;
		अवरोध;
	हाल 16:
		val |= AC_FMT_BITS_16;
		अवरोध;
	हाल 20:
	हाल 24:
	हाल 32:
		अगर (maxbps >= 32 || क्रमmat == SNDRV_PCM_FORMAT_FLOAT_LE)
			val |= AC_FMT_BITS_32;
		अन्यथा अगर (maxbps >= 24)
			val |= AC_FMT_BITS_24;
		अन्यथा
			val |= AC_FMT_BITS_20;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (spdअगर_ctls & AC_DIG1_NONAUDIO)
		val |= AC_FMT_TYPE_NON_PCM;

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_calc_stream_क्रमmat);

अटल अचिन्हित पूर्णांक query_pcm_param(काष्ठा hdac_device *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक val = 0;

	अगर (nid != codec->afg &&
	    (get_wcaps(codec, nid) & AC_WCAP_FORMAT_OVRD))
		val = snd_hdac_पढ़ो_parm(codec, nid, AC_PAR_PCM);
	अगर (!val || val == -1)
		val = snd_hdac_पढ़ो_parm(codec, codec->afg, AC_PAR_PCM);
	अगर (!val || val == -1)
		वापस 0;
	वापस val;
पूर्ण

अटल अचिन्हित पूर्णांक query_stream_param(काष्ठा hdac_device *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक streams = snd_hdac_पढ़ो_parm(codec, nid, AC_PAR_STREAM);

	अगर (!streams || streams == -1)
		streams = snd_hdac_पढ़ो_parm(codec, codec->afg, AC_PAR_STREAM);
	अगर (!streams || streams == -1)
		वापस 0;
	वापस streams;
पूर्ण

/**
 * snd_hdac_query_supported_pcm - query the supported PCM rates and क्रमmats
 * @codec: the codec object
 * @nid: NID to query
 * @ratesp: the poपूर्णांकer to store the detected rate bitflags
 * @क्रमmatsp: the poपूर्णांकer to store the detected क्रमmats
 * @bpsp: the poपूर्णांकer to store the detected क्रमmat widths
 *
 * Queries the supported PCM rates and क्रमmats.  The शून्य @ratesp, @क्रमmatsp
 * or @bsps argument is ignored.
 *
 * Returns 0 अगर successful, otherwise a negative error code.
 */
पूर्णांक snd_hdac_query_supported_pcm(काष्ठा hdac_device *codec, hda_nid_t nid,
				 u32 *ratesp, u64 *क्रमmatsp, अचिन्हित पूर्णांक *bpsp)
अणु
	अचिन्हित पूर्णांक i, val, wcaps;

	wcaps = get_wcaps(codec, nid);
	val = query_pcm_param(codec, nid);

	अगर (ratesp) अणु
		u32 rates = 0;
		क्रम (i = 0; i < AC_PAR_PCM_RATE_BITS; i++) अणु
			अगर (val & (1 << i))
				rates |= rate_bits[i].alsa_bits;
		पूर्ण
		अगर (rates == 0) अणु
			dev_err(&codec->dev,
				"rates == 0 (nid=0x%x, val=0x%x, ovrd=%i)\n",
				nid, val,
				(wcaps & AC_WCAP_FORMAT_OVRD) ? 1 : 0);
			वापस -EIO;
		पूर्ण
		*ratesp = rates;
	पूर्ण

	अगर (क्रमmatsp || bpsp) अणु
		u64 क्रमmats = 0;
		अचिन्हित पूर्णांक streams, bps;

		streams = query_stream_param(codec, nid);
		अगर (!streams)
			वापस -EIO;

		bps = 0;
		अगर (streams & AC_SUPFMT_PCM) अणु
			अगर (val & AC_SUPPCM_BITS_8) अणु
				क्रमmats |= SNDRV_PCM_FMTBIT_U8;
				bps = 8;
			पूर्ण
			अगर (val & AC_SUPPCM_BITS_16) अणु
				क्रमmats |= SNDRV_PCM_FMTBIT_S16_LE;
				bps = 16;
			पूर्ण
			अगर (wcaps & AC_WCAP_DIGITAL) अणु
				अगर (val & AC_SUPPCM_BITS_32)
					क्रमmats |= SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE;
				अगर (val & (AC_SUPPCM_BITS_20|AC_SUPPCM_BITS_24))
					क्रमmats |= SNDRV_PCM_FMTBIT_S32_LE;
				अगर (val & AC_SUPPCM_BITS_24)
					bps = 24;
				अन्यथा अगर (val & AC_SUPPCM_BITS_20)
					bps = 20;
			पूर्ण अन्यथा अगर (val & (AC_SUPPCM_BITS_20|AC_SUPPCM_BITS_24|
					  AC_SUPPCM_BITS_32)) अणु
				क्रमmats |= SNDRV_PCM_FMTBIT_S32_LE;
				अगर (val & AC_SUPPCM_BITS_32)
					bps = 32;
				अन्यथा अगर (val & AC_SUPPCM_BITS_24)
					bps = 24;
				अन्यथा अगर (val & AC_SUPPCM_BITS_20)
					bps = 20;
			पूर्ण
		पूर्ण
#अगर 0 /* FIXME: CS4206 करोesn't work, which is the only codec supporting भग्न */
		अगर (streams & AC_SUPFMT_FLOAT32) अणु
			क्रमmats |= SNDRV_PCM_FMTBIT_FLOAT_LE;
			अगर (!bps)
				bps = 32;
		पूर्ण
#पूर्ण_अगर
		अगर (streams == AC_SUPFMT_AC3) अणु
			/* should be exclusive */
			/* temporary hack: we have still no proper support
			 * क्रम the direct AC3 stream...
			 */
			क्रमmats |= SNDRV_PCM_FMTBIT_U8;
			bps = 8;
		पूर्ण
		अगर (क्रमmats == 0) अणु
			dev_err(&codec->dev,
				"formats == 0 (nid=0x%x, val=0x%x, ovrd=%i, streams=0x%x)\n",
				nid, val,
				(wcaps & AC_WCAP_FORMAT_OVRD) ? 1 : 0,
				streams);
			वापस -EIO;
		पूर्ण
		अगर (क्रमmatsp)
			*क्रमmatsp = क्रमmats;
		अगर (bpsp)
			*bpsp = bps;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_query_supported_pcm);

/**
 * snd_hdac_is_supported_क्रमmat - Check the validity of the क्रमmat
 * @codec: the codec object
 * @nid: NID to check
 * @क्रमmat: the HD-audio क्रमmat value to check
 *
 * Check whether the given node supports the क्रमmat value.
 *
 * Returns true अगर supported, false अगर not.
 */
bool snd_hdac_is_supported_क्रमmat(काष्ठा hdac_device *codec, hda_nid_t nid,
				  अचिन्हित पूर्णांक क्रमmat)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक val = 0, rate, stream;

	val = query_pcm_param(codec, nid);
	अगर (!val)
		वापस false;

	rate = क्रमmat & 0xff00;
	क्रम (i = 0; i < AC_PAR_PCM_RATE_BITS; i++)
		अगर (rate_bits[i].hda_fmt == rate) अणु
			अगर (val & (1 << i))
				अवरोध;
			वापस false;
		पूर्ण
	अगर (i >= AC_PAR_PCM_RATE_BITS)
		वापस false;

	stream = query_stream_param(codec, nid);
	अगर (!stream)
		वापस false;

	अगर (stream & AC_SUPFMT_PCM) अणु
		चयन (क्रमmat & 0xf0) अणु
		हाल 0x00:
			अगर (!(val & AC_SUPPCM_BITS_8))
				वापस false;
			अवरोध;
		हाल 0x10:
			अगर (!(val & AC_SUPPCM_BITS_16))
				वापस false;
			अवरोध;
		हाल 0x20:
			अगर (!(val & AC_SUPPCM_BITS_20))
				वापस false;
			अवरोध;
		हाल 0x30:
			अगर (!(val & AC_SUPPCM_BITS_24))
				वापस false;
			अवरोध;
		हाल 0x40:
			अगर (!(val & AC_SUPPCM_BITS_32))
				वापस false;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* FIXME: check क्रम भग्न32 and AC3? */
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_is_supported_क्रमmat);

अटल अचिन्हित पूर्णांक codec_पढ़ो(काष्ठा hdac_device *hdac, hda_nid_t nid,
			पूर्णांक flags, अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm)
अणु
	अचिन्हित पूर्णांक cmd = snd_hdac_make_cmd(hdac, nid, verb, parm);
	अचिन्हित पूर्णांक res;

	अगर (snd_hdac_exec_verb(hdac, cmd, flags, &res))
		वापस -1;

	वापस res;
पूर्ण

अटल पूर्णांक codec_ग_लिखो(काष्ठा hdac_device *hdac, hda_nid_t nid,
			पूर्णांक flags, अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm)
अणु
	अचिन्हित पूर्णांक cmd = snd_hdac_make_cmd(hdac, nid, verb, parm);

	वापस snd_hdac_exec_verb(hdac, cmd, flags, शून्य);
पूर्ण

/**
 * snd_hdac_codec_पढ़ो - send a command and get the response
 * @hdac: the HDAC device
 * @nid: NID to send the command
 * @flags: optional bit flags
 * @verb: the verb to send
 * @parm: the parameter क्रम the verb
 *
 * Send a single command and पढ़ो the corresponding response.
 *
 * Returns the obtained response value, or -1 क्रम an error.
 */
पूर्णांक snd_hdac_codec_पढ़ो(काष्ठा hdac_device *hdac, hda_nid_t nid,
			पूर्णांक flags, अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm)
अणु
	वापस codec_पढ़ो(hdac, nid, flags, verb, parm);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_codec_पढ़ो);

/**
 * snd_hdac_codec_ग_लिखो - send a single command without रुकोing क्रम response
 * @hdac: the HDAC device
 * @nid: NID to send the command
 * @flags: optional bit flags
 * @verb: the verb to send
 * @parm: the parameter क्रम the verb
 *
 * Send a single command without रुकोing क्रम response.
 *
 * Returns 0 अगर successful, or a negative error code.
 */
पूर्णांक snd_hdac_codec_ग_लिखो(काष्ठा hdac_device *hdac, hda_nid_t nid,
			पूर्णांक flags, अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm)
अणु
	वापस codec_ग_लिखो(hdac, nid, flags, verb, parm);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_codec_ग_लिखो);

/**
 * snd_hdac_check_घातer_state - check whether the actual घातer state matches
 * with the target state
 *
 * @hdac: the HDAC device
 * @nid: NID to send the command
 * @target_state: target state to check क्रम
 *
 * Return true अगर state matches, false अगर not
 */
bool snd_hdac_check_घातer_state(काष्ठा hdac_device *hdac,
		hda_nid_t nid, अचिन्हित पूर्णांक target_state)
अणु
	अचिन्हित पूर्णांक state = codec_पढ़ो(hdac, nid, 0,
				AC_VERB_GET_POWER_STATE, 0);

	अगर (state & AC_PWRST_ERROR)
		वापस true;
	state = (state >> 4) & 0x0f;
	वापस (state == target_state);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_check_घातer_state);
/**
 * snd_hdac_sync_घातer_state - रुको until actual घातer state matches
 * with the target state
 *
 * @codec: the HDAC device
 * @nid: NID to send the command
 * @घातer_state: target घातer state to रुको क्रम
 *
 * Return घातer state or PS_ERROR अगर codec rejects GET verb.
 */
अचिन्हित पूर्णांक snd_hdac_sync_घातer_state(काष्ठा hdac_device *codec,
			hda_nid_t nid, अचिन्हित पूर्णांक घातer_state)
अणु
	अचिन्हित दीर्घ end_समय = jअगरfies + msecs_to_jअगरfies(500);
	अचिन्हित पूर्णांक state, actual_state, count;

	क्रम (count = 0; count < 500; count++) अणु
		state = snd_hdac_codec_पढ़ो(codec, nid, 0,
				AC_VERB_GET_POWER_STATE, 0);
		अगर (state & AC_PWRST_ERROR) अणु
			msleep(20);
			अवरोध;
		पूर्ण
		actual_state = (state >> 4) & 0x0f;
		अगर (actual_state == घातer_state)
			अवरोध;
		अगर (समय_after_eq(jअगरfies, end_समय))
			अवरोध;
		/* रुको until the codec reachs to the target state */
		msleep(1);
	पूर्ण
	वापस state;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_sync_घातer_state);
