<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Universal Interface क्रम Intel High Definition Audio Codec
 *
 * Generic widget tree parser
 *
 * Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/sort.h>
#समावेश <linux/delay.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/leds.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/tlv.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश "hda_auto_parser.h"
#समावेश "hda_jack.h"
#समावेश "hda_beep.h"
#समावेश "hda_generic.h"


/**
 * snd_hda_gen_spec_init - initialize hda_gen_spec काष्ठा
 * @spec: hda_gen_spec object to initialize
 *
 * Initialize the given hda_gen_spec object.
 */
पूर्णांक snd_hda_gen_spec_init(काष्ठा hda_gen_spec *spec)
अणु
	snd_array_init(&spec->kctls, माप(काष्ठा snd_kcontrol_new), 32);
	snd_array_init(&spec->paths, माप(काष्ठा nid_path), 8);
	snd_array_init(&spec->loopback_list, माप(काष्ठा hda_amp_list), 8);
	mutex_init(&spec->pcm_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_spec_init);

/**
 * snd_hda_gen_add_kctl - Add a new kctl_new काष्ठा from the ढाँचा
 * @spec: hda_gen_spec object
 * @name: name string to override the ढाँचा, शून्य अगर unchanged
 * @temp: ढाँचा क्रम the new kctl
 *
 * Add a new kctl (actually snd_kcontrol_new to be instantiated later)
 * element based on the given snd_kcontrol_new ढाँचा @temp and the
 * name string @name to the list in @spec.
 * Returns the newly created object or शून्य as error.
 */
काष्ठा snd_kcontrol_new *
snd_hda_gen_add_kctl(काष्ठा hda_gen_spec *spec, स्थिर अक्षर *name,
		     स्थिर काष्ठा snd_kcontrol_new *temp)
अणु
	काष्ठा snd_kcontrol_new *knew = snd_array_new(&spec->kctls);
	अगर (!knew)
		वापस शून्य;
	*knew = *temp;
	अगर (name)
		knew->name = kstrdup(name, GFP_KERNEL);
	अन्यथा अगर (knew->name)
		knew->name = kstrdup(knew->name, GFP_KERNEL);
	अगर (!knew->name)
		वापस शून्य;
	वापस knew;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_add_kctl);

अटल व्योम मुक्त_kctls(काष्ठा hda_gen_spec *spec)
अणु
	अगर (spec->kctls.list) अणु
		काष्ठा snd_kcontrol_new *kctl = spec->kctls.list;
		पूर्णांक i;
		क्रम (i = 0; i < spec->kctls.used; i++)
			kमुक्त(kctl[i].name);
	पूर्ण
	snd_array_मुक्त(&spec->kctls);
पूर्ण

अटल व्योम snd_hda_gen_spec_मुक्त(काष्ठा hda_gen_spec *spec)
अणु
	अगर (!spec)
		वापस;
	मुक्त_kctls(spec);
	snd_array_मुक्त(&spec->paths);
	snd_array_मुक्त(&spec->loopback_list);
पूर्ण

/*
 * store user hपूर्णांकs
 */
अटल व्योम parse_user_hपूर्णांकs(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक val;

	val = snd_hda_get_bool_hपूर्णांक(codec, "jack_detect");
	अगर (val >= 0)
		codec->no_jack_detect = !val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "inv_jack_detect");
	अगर (val >= 0)
		codec->inv_jack_detect = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "trigger_sense");
	अगर (val >= 0)
		codec->no_trigger_sense = !val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "inv_eapd");
	अगर (val >= 0)
		codec->inv_eapd = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "pcm_format_first");
	अगर (val >= 0)
		codec->pcm_क्रमmat_first = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "sticky_stream");
	अगर (val >= 0)
		codec->no_sticky_stream = !val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "spdif_status_reset");
	अगर (val >= 0)
		codec->spdअगर_status_reset = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "pin_amp_workaround");
	अगर (val >= 0)
		codec->pin_amp_workaround = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "single_adc_amp");
	अगर (val >= 0)
		codec->single_adc_amp = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "power_save_node");
	अगर (val >= 0)
		codec->घातer_save_node = !!val;

	val = snd_hda_get_bool_hपूर्णांक(codec, "auto_mute");
	अगर (val >= 0)
		spec->suppress_स्वतः_mute = !val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "auto_mic");
	अगर (val >= 0)
		spec->suppress_स्वतः_mic = !val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "line_in_auto_switch");
	अगर (val >= 0)
		spec->line_in_स्वतः_चयन = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "auto_mute_via_amp");
	अगर (val >= 0)
		spec->स्वतः_mute_via_amp = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "need_dac_fix");
	अगर (val >= 0)
		spec->need_dac_fix = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "primary_hp");
	अगर (val >= 0)
		spec->no_primary_hp = !val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "multi_io");
	अगर (val >= 0)
		spec->no_multi_io = !val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "multi_cap_vol");
	अगर (val >= 0)
		spec->multi_cap_vol = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "inv_dmic_split");
	अगर (val >= 0)
		spec->inv_dmic_split = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "indep_hp");
	अगर (val >= 0)
		spec->indep_hp = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "add_stereo_mix_input");
	अगर (val >= 0)
		spec->add_stereo_mix_input = !!val;
	/* the following two are just क्रम compatibility */
	val = snd_hda_get_bool_hपूर्णांक(codec, "add_out_jack_modes");
	अगर (val >= 0)
		spec->add_jack_modes = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "add_in_jack_modes");
	अगर (val >= 0)
		spec->add_jack_modes = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "add_jack_modes");
	अगर (val >= 0)
		spec->add_jack_modes = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "power_down_unused");
	अगर (val >= 0)
		spec->घातer_करोwn_unused = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "add_hp_mic");
	अगर (val >= 0)
		spec->hp_mic = !!val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "hp_mic_detect");
	अगर (val >= 0)
		spec->suppress_hp_mic_detect = !val;
	val = snd_hda_get_bool_hपूर्णांक(codec, "vmaster");
	अगर (val >= 0)
		spec->suppress_vmaster = !val;

	अगर (!snd_hda_get_पूर्णांक_hपूर्णांक(codec, "mixer_nid", &val))
		spec->mixer_nid = val;
पूर्ण

/*
 * pin control value accesses
 */

#घोषणा update_pin_ctl(codec, pin, val) \
	snd_hda_codec_ग_लिखो_cache(codec, pin, 0, \
				   AC_VERB_SET_PIN_WIDGET_CONTROL, val)

/* restore the pinctl based on the cached value */
अटल अंतरभूत व्योम restore_pin_ctl(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	update_pin_ctl(codec, pin, snd_hda_codec_get_pin_target(codec, pin));
पूर्ण

/* set the pinctl target value and ग_लिखो it अगर requested */
अटल व्योम set_pin_target(काष्ठा hda_codec *codec, hda_nid_t pin,
			   अचिन्हित पूर्णांक val, bool करो_ग_लिखो)
अणु
	अगर (!pin)
		वापस;
	val = snd_hda_correct_pin_ctl(codec, pin, val);
	snd_hda_codec_set_pin_target(codec, pin, val);
	अगर (करो_ग_लिखो)
		update_pin_ctl(codec, pin, val);
पूर्ण

/* set pinctl target values क्रम all given pins */
अटल व्योम set_pin_tarमाला_लो(काष्ठा hda_codec *codec, पूर्णांक num_pins,
			    hda_nid_t *pins, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < num_pins; i++)
		set_pin_target(codec, pins[i], val, false);
पूर्ण

/*
 * parsing paths
 */

/* वापस the position of NID in the list, or -1 अगर not found */
अटल पूर्णांक find_idx_in_nid_list(hda_nid_t nid, स्थिर hda_nid_t *list, पूर्णांक nums)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < nums; i++)
		अगर (list[i] == nid)
			वापस i;
	वापस -1;
पूर्ण

/* वापस true अगर the given NID is contained in the path */
अटल bool is_nid_contained(काष्ठा nid_path *path, hda_nid_t nid)
अणु
	वापस find_idx_in_nid_list(nid, path->path, path->depth) >= 0;
पूर्ण

अटल काष्ठा nid_path *get_nid_path(काष्ठा hda_codec *codec,
				     hda_nid_t from_nid, hda_nid_t to_nid,
				     पूर्णांक anchor_nid)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा nid_path *path;
	पूर्णांक i;

	snd_array_क्रम_each(&spec->paths, i, path) अणु
		अगर (path->depth <= 0)
			जारी;
		अगर ((!from_nid || path->path[0] == from_nid) &&
		    (!to_nid || path->path[path->depth - 1] == to_nid)) अणु
			अगर (!anchor_nid ||
			    (anchor_nid > 0 && is_nid_contained(path, anchor_nid)) ||
			    (anchor_nid < 0 && !is_nid_contained(path, anchor_nid)))
				वापस path;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * snd_hda_get_path_idx - get the index number corresponding to the path
 * instance
 * @codec: the HDA codec
 * @path: nid_path object
 *
 * The वापसed index starts from 1, i.e. the actual array index with offset 1,
 * and zero is handled as an invalid path
 */
पूर्णांक snd_hda_get_path_idx(काष्ठा hda_codec *codec, काष्ठा nid_path *path)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा nid_path *array = spec->paths.list;
	sमाप_प्रकार idx;

	अगर (!spec->paths.used)
		वापस 0;
	idx = path - array;
	अगर (idx < 0 || idx >= spec->paths.used)
		वापस 0;
	वापस idx + 1;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_path_idx);

/**
 * snd_hda_get_path_from_idx - get the path instance corresponding to the
 * given index number
 * @codec: the HDA codec
 * @idx: the path index
 */
काष्ठा nid_path *snd_hda_get_path_from_idx(काष्ठा hda_codec *codec, पूर्णांक idx)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;

	अगर (idx <= 0 || idx > spec->paths.used)
		वापस शून्य;
	वापस snd_array_elem(&spec->paths, idx - 1);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_path_from_idx);

/* check whether the given DAC is alपढ़ोy found in any existing paths */
अटल bool is_dac_alपढ़ोy_used(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	स्थिर काष्ठा nid_path *path;
	पूर्णांक i;

	snd_array_क्रम_each(&spec->paths, i, path) अणु
		अगर (path->path[0] == nid)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* check whether the given two widमाला_लो can be connected */
अटल bool is_reachable_path(काष्ठा hda_codec *codec,
			      hda_nid_t from_nid, hda_nid_t to_nid)
अणु
	अगर (!from_nid || !to_nid)
		वापस false;
	वापस snd_hda_get_conn_index(codec, to_nid, from_nid, true) >= 0;
पूर्ण

/* nid, dir and idx */
#घोषणा AMP_VAL_COMPARE_MASK	(0xffff | (1U << 18) | (0x0f << 19))

/* check whether the given ctl is alपढ़ोy asचिन्हित in any path elements */
अटल bool is_ctl_used(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक val, पूर्णांक type)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	स्थिर काष्ठा nid_path *path;
	पूर्णांक i;

	val &= AMP_VAL_COMPARE_MASK;
	snd_array_क्रम_each(&spec->paths, i, path) अणु
		अगर ((path->ctls[type] & AMP_VAL_COMPARE_MASK) == val)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* check whether a control with the given (nid, dir, idx) was asचिन्हित */
अटल bool is_ctl_associated(काष्ठा hda_codec *codec, hda_nid_t nid,
			      पूर्णांक dir, पूर्णांक idx, पूर्णांक type)
अणु
	अचिन्हित पूर्णांक val = HDA_COMPOSE_AMP_VAL(nid, 3, idx, dir);
	वापस is_ctl_used(codec, val, type);
पूर्ण

अटल व्योम prपूर्णांक_nid_path(काष्ठा hda_codec *codec,
			   स्थिर अक्षर *pfx, काष्ठा nid_path *path)
अणु
	अक्षर buf[40];
	अक्षर *pos = buf;
	पूर्णांक i;

	*pos = 0;
	क्रम (i = 0; i < path->depth; i++)
		pos += scnम_लिखो(pos, माप(buf) - (pos - buf), "%s%02x",
				 pos != buf ? ":" : "",
				 path->path[i]);

	codec_dbg(codec, "%s path: depth=%d '%s'\n", pfx, path->depth, buf);
पूर्ण

/* called recursively */
अटल bool __parse_nid_path(काष्ठा hda_codec *codec,
			     hda_nid_t from_nid, hda_nid_t to_nid,
			     पूर्णांक anchor_nid, काष्ठा nid_path *path,
			     पूर्णांक depth)
अणु
	स्थिर hda_nid_t *conn;
	पूर्णांक i, nums;

	अगर (to_nid == anchor_nid)
		anchor_nid = 0; /* anchor passed */
	अन्यथा अगर (to_nid == (hda_nid_t)(-anchor_nid))
		वापस false; /* hit the exclusive nid */

	nums = snd_hda_get_conn_list(codec, to_nid, &conn);
	क्रम (i = 0; i < nums; i++) अणु
		अगर (conn[i] != from_nid) अणु
			/* special हाल: when from_nid is 0,
			 * try to find an empty DAC
			 */
			अगर (from_nid ||
			    get_wcaps_type(get_wcaps(codec, conn[i])) != AC_WID_AUD_OUT ||
			    is_dac_alपढ़ोy_used(codec, conn[i]))
				जारी;
		पूर्ण
		/* anchor is not requested or alपढ़ोy passed? */
		अगर (anchor_nid <= 0)
			जाओ found;
	पूर्ण
	अगर (depth >= MAX_NID_PATH_DEPTH)
		वापस false;
	क्रम (i = 0; i < nums; i++) अणु
		अचिन्हित पूर्णांक type;
		type = get_wcaps_type(get_wcaps(codec, conn[i]));
		अगर (type == AC_WID_AUD_OUT || type == AC_WID_AUD_IN ||
		    type == AC_WID_PIN)
			जारी;
		अगर (__parse_nid_path(codec, from_nid, conn[i],
				     anchor_nid, path, depth + 1))
			जाओ found;
	पूर्ण
	वापस false;

 found:
	path->path[path->depth] = conn[i];
	path->idx[path->depth + 1] = i;
	अगर (nums > 1 && get_wcaps_type(get_wcaps(codec, to_nid)) != AC_WID_AUD_MIX)
		path->multi[path->depth + 1] = 1;
	path->depth++;
	वापस true;
पूर्ण

/*
 * snd_hda_parse_nid_path - parse the widget path from the given nid to
 * the target nid
 * @codec: the HDA codec
 * @from_nid: the NID where the path start from
 * @to_nid: the NID where the path ends at
 * @anchor_nid: the anchor indication
 * @path: the path object to store the result
 *
 * Returns true अगर a matching path is found.
 *
 * The parsing behavior depends on parameters:
 * when @from_nid is 0, try to find an empty DAC;
 * when @anchor_nid is set to a positive value, only paths through the widget
 * with the given value are evaluated.
 * when @anchor_nid is set to a negative value, paths through the widget
 * with the negative of given value are excluded, only other paths are chosen.
 * when @anchor_nid is zero, no special handling about path selection.
 */
अटल bool snd_hda_parse_nid_path(काष्ठा hda_codec *codec, hda_nid_t from_nid,
			    hda_nid_t to_nid, पूर्णांक anchor_nid,
			    काष्ठा nid_path *path)
अणु
	अगर (__parse_nid_path(codec, from_nid, to_nid, anchor_nid, path, 1)) अणु
		path->path[path->depth] = to_nid;
		path->depth++;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * snd_hda_add_new_path - parse the path between the given NIDs and
 * add to the path list
 * @codec: the HDA codec
 * @from_nid: the NID where the path start from
 * @to_nid: the NID where the path ends at
 * @anchor_nid: the anchor indication, see snd_hda_parse_nid_path()
 *
 * If no valid path is found, वापसs शून्य.
 */
काष्ठा nid_path *
snd_hda_add_new_path(काष्ठा hda_codec *codec, hda_nid_t from_nid,
		     hda_nid_t to_nid, पूर्णांक anchor_nid)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा nid_path *path;

	अगर (from_nid && to_nid && !is_reachable_path(codec, from_nid, to_nid))
		वापस शून्य;

	/* check whether the path has been alपढ़ोy added */
	path = get_nid_path(codec, from_nid, to_nid, anchor_nid);
	अगर (path)
		वापस path;

	path = snd_array_new(&spec->paths);
	अगर (!path)
		वापस शून्य;
	स_रखो(path, 0, माप(*path));
	अगर (snd_hda_parse_nid_path(codec, from_nid, to_nid, anchor_nid, path))
		वापस path;
	/* push back */
	spec->paths.used--;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_add_new_path);

/* clear the given path as invalid so that it won't be picked up later */
अटल व्योम invalidate_nid_path(काष्ठा hda_codec *codec, पूर्णांक idx)
अणु
	काष्ठा nid_path *path = snd_hda_get_path_from_idx(codec, idx);
	अगर (!path)
		वापस;
	स_रखो(path, 0, माप(*path));
पूर्ण

/* वापस a DAC अगर paired to the given pin by codec driver */
अटल hda_nid_t get_preferred_dac(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	स्थिर hda_nid_t *list = spec->preferred_dacs;

	अगर (!list)
		वापस 0;
	क्रम (; *list; list += 2)
		अगर (*list == pin)
			वापस list[1];
	वापस 0;
पूर्ण

/* look क्रम an empty DAC slot */
अटल hda_nid_t look_क्रम_dac(काष्ठा hda_codec *codec, hda_nid_t pin,
			      bool is_digital)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	bool cap_digital;
	पूर्णांक i;

	क्रम (i = 0; i < spec->num_all_dacs; i++) अणु
		hda_nid_t nid = spec->all_dacs[i];
		अगर (!nid || is_dac_alपढ़ोy_used(codec, nid))
			जारी;
		cap_digital = !!(get_wcaps(codec, nid) & AC_WCAP_DIGITAL);
		अगर (is_digital != cap_digital)
			जारी;
		अगर (is_reachable_path(codec, nid, pin))
			वापस nid;
	पूर्ण
	वापस 0;
पूर्ण

/* replace the channels in the composed amp value with the given number */
अटल अचिन्हित पूर्णांक amp_val_replace_channels(अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक chs)
अणु
	val &= ~(0x3U << 16);
	val |= chs << 16;
	वापस val;
पूर्ण

अटल bool same_amp_caps(काष्ठा hda_codec *codec, hda_nid_t nid1,
			  hda_nid_t nid2, पूर्णांक dir)
अणु
	अगर (!(get_wcaps(codec, nid1) & (1 << (dir + 1))))
		वापस !(get_wcaps(codec, nid2) & (1 << (dir + 1)));
	वापस (query_amp_caps(codec, nid1, dir) ==
		query_amp_caps(codec, nid2, dir));
पूर्ण

/* look क्रम a widget suitable क्रम assigning a mute चयन in the path */
अटल hda_nid_t look_क्रम_out_mute_nid(काष्ठा hda_codec *codec,
				       काष्ठा nid_path *path)
अणु
	पूर्णांक i;

	क्रम (i = path->depth - 1; i >= 0; i--) अणु
		अगर (nid_has_mute(codec, path->path[i], HDA_OUTPUT))
			वापस path->path[i];
		अगर (i != path->depth - 1 && i != 0 &&
		    nid_has_mute(codec, path->path[i], HDA_INPUT))
			वापस path->path[i];
	पूर्ण
	वापस 0;
पूर्ण

/* look क्रम a widget suitable क्रम assigning a volume ctl in the path */
अटल hda_nid_t look_क्रम_out_vol_nid(काष्ठा hda_codec *codec,
				      काष्ठा nid_path *path)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i;

	क्रम (i = path->depth - 1; i >= 0; i--) अणु
		hda_nid_t nid = path->path[i];
		अगर ((spec->out_vol_mask >> nid) & 1)
			जारी;
		अगर (nid_has_volume(codec, nid, HDA_OUTPUT))
			वापस nid;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * path activation / deactivation
 */

/* can have the amp-in capability? */
अटल bool has_amp_in(काष्ठा hda_codec *codec, काष्ठा nid_path *path, पूर्णांक idx)
अणु
	hda_nid_t nid = path->path[idx];
	अचिन्हित पूर्णांक caps = get_wcaps(codec, nid);
	अचिन्हित पूर्णांक type = get_wcaps_type(caps);

	अगर (!(caps & AC_WCAP_IN_AMP))
		वापस false;
	अगर (type == AC_WID_PIN && idx > 0) /* only क्रम input pins */
		वापस false;
	वापस true;
पूर्ण

/* can have the amp-out capability? */
अटल bool has_amp_out(काष्ठा hda_codec *codec, काष्ठा nid_path *path, पूर्णांक idx)
अणु
	hda_nid_t nid = path->path[idx];
	अचिन्हित पूर्णांक caps = get_wcaps(codec, nid);
	अचिन्हित पूर्णांक type = get_wcaps_type(caps);

	अगर (!(caps & AC_WCAP_OUT_AMP))
		वापस false;
	अगर (type == AC_WID_PIN && !idx) /* only क्रम output pins */
		वापस false;
	वापस true;
पूर्ण

/* check whether the given (nid,dir,idx) is active */
अटल bool is_active_nid(काष्ठा hda_codec *codec, hda_nid_t nid,
			  अचिन्हित पूर्णांक dir, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक type = get_wcaps_type(get_wcaps(codec, nid));
	स्थिर काष्ठा nid_path *path;
	पूर्णांक i, n;

	अगर (nid == codec->core.afg)
		वापस true;

	snd_array_क्रम_each(&spec->paths, n, path) अणु
		अगर (!path->active)
			जारी;
		अगर (codec->घातer_save_node) अणु
			अगर (!path->stream_enabled)
				जारी;
			/* ignore unplugged paths except क्रम DAC/ADC */
			अगर (!(path->pin_enabled || path->pin_fixed) &&
			    type != AC_WID_AUD_OUT && type != AC_WID_AUD_IN)
				जारी;
		पूर्ण
		क्रम (i = 0; i < path->depth; i++) अणु
			अगर (path->path[i] == nid) अणु
				अगर (dir == HDA_OUTPUT || idx == -1 ||
				    path->idx[i] == idx)
					वापस true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/* check whether the NID is referred by any active paths */
#घोषणा is_active_nid_क्रम_any(codec, nid) \
	is_active_nid(codec, nid, HDA_OUTPUT, -1)

/* get the शेष amp value क्रम the target state */
अटल पूर्णांक get_amp_val_to_activate(काष्ठा hda_codec *codec, hda_nid_t nid,
				   पूर्णांक dir, अचिन्हित पूर्णांक caps, bool enable)
अणु
	अचिन्हित पूर्णांक val = 0;

	अगर (caps & AC_AMPCAP_NUM_STEPS) अणु
		/* set to 0dB */
		अगर (enable)
			val = (caps & AC_AMPCAP_OFFSET) >> AC_AMPCAP_OFFSET_SHIFT;
	पूर्ण
	अगर (caps & (AC_AMPCAP_MUTE | AC_AMPCAP_MIN_MUTE)) अणु
		अगर (!enable)
			val |= HDA_AMP_MUTE;
	पूर्ण
	वापस val;
पूर्ण

/* is this a stereo widget or a stereo-to-mono mix? */
अटल bool is_stereo_amps(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dir)
अणु
	अचिन्हित पूर्णांक wcaps = get_wcaps(codec, nid);
	hda_nid_t conn;

	अगर (wcaps & AC_WCAP_STEREO)
		वापस true;
	अगर (dir != HDA_INPUT || get_wcaps_type(wcaps) != AC_WID_AUD_MIX)
		वापस false;
	अगर (snd_hda_get_num_conns(codec, nid) != 1)
		वापस false;
	अगर (snd_hda_get_connections(codec, nid, &conn, 1) < 0)
		वापस false;
	वापस !!(get_wcaps(codec, conn) & AC_WCAP_STEREO);
पूर्ण

/* initialize the amp value (only at the first समय) */
अटल व्योम init_amp(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dir, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक caps = query_amp_caps(codec, nid, dir);
	पूर्णांक val = get_amp_val_to_activate(codec, nid, dir, caps, false);

	अगर (is_stereo_amps(codec, nid, dir))
		snd_hda_codec_amp_init_stereo(codec, nid, dir, idx, 0xff, val);
	अन्यथा
		snd_hda_codec_amp_init(codec, nid, 0, dir, idx, 0xff, val);
पूर्ण

/* update the amp, करोing in stereo or mono depending on NID */
अटल पूर्णांक update_amp(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dir, पूर्णांक idx,
		      अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	अगर (is_stereo_amps(codec, nid, dir))
		वापस snd_hda_codec_amp_stereo(codec, nid, dir, idx,
						mask, val);
	अन्यथा
		वापस snd_hda_codec_amp_update(codec, nid, 0, dir, idx,
						mask, val);
पूर्ण

/* calculate amp value mask we can modअगरy;
 * अगर the given amp is controlled by mixers, करोn't touch it
 */
अटल अचिन्हित पूर्णांक get_amp_mask_to_modअगरy(काष्ठा hda_codec *codec,
					   hda_nid_t nid, पूर्णांक dir, पूर्णांक idx,
					   अचिन्हित पूर्णांक caps)
अणु
	अचिन्हित पूर्णांक mask = 0xff;

	अगर (caps & (AC_AMPCAP_MUTE | AC_AMPCAP_MIN_MUTE)) अणु
		अगर (is_ctl_associated(codec, nid, dir, idx, NID_PATH_MUTE_CTL))
			mask &= ~0x80;
	पूर्ण
	अगर (caps & AC_AMPCAP_NUM_STEPS) अणु
		अगर (is_ctl_associated(codec, nid, dir, idx, NID_PATH_VOL_CTL) ||
		    is_ctl_associated(codec, nid, dir, idx, NID_PATH_BOOST_CTL))
			mask &= ~0x7f;
	पूर्ण
	वापस mask;
पूर्ण

अटल व्योम activate_amp(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dir,
			 पूर्णांक idx, पूर्णांक idx_to_check, bool enable)
अणु
	अचिन्हित पूर्णांक caps;
	अचिन्हित पूर्णांक mask, val;

	caps = query_amp_caps(codec, nid, dir);
	val = get_amp_val_to_activate(codec, nid, dir, caps, enable);
	mask = get_amp_mask_to_modअगरy(codec, nid, dir, idx_to_check, caps);
	अगर (!mask)
		वापस;

	val &= mask;
	update_amp(codec, nid, dir, idx, mask, val);
पूर्ण

अटल व्योम check_and_activate_amp(काष्ठा hda_codec *codec, hda_nid_t nid,
				   पूर्णांक dir, पूर्णांक idx, पूर्णांक idx_to_check,
				   bool enable)
अणु
	/* check whether the given amp is still used by others */
	अगर (!enable && is_active_nid(codec, nid, dir, idx_to_check))
		वापस;
	activate_amp(codec, nid, dir, idx, idx_to_check, enable);
पूर्ण

अटल व्योम activate_amp_out(काष्ठा hda_codec *codec, काष्ठा nid_path *path,
			     पूर्णांक i, bool enable)
अणु
	hda_nid_t nid = path->path[i];
	init_amp(codec, nid, HDA_OUTPUT, 0);
	check_and_activate_amp(codec, nid, HDA_OUTPUT, 0, 0, enable);
पूर्ण

अटल व्योम activate_amp_in(काष्ठा hda_codec *codec, काष्ठा nid_path *path,
			    पूर्णांक i, bool enable, bool add_aamix)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	स्थिर hda_nid_t *conn;
	पूर्णांक n, nums, idx;
	पूर्णांक type;
	hda_nid_t nid = path->path[i];

	nums = snd_hda_get_conn_list(codec, nid, &conn);
	अगर (nums < 0)
		वापस;
	type = get_wcaps_type(get_wcaps(codec, nid));
	अगर (type == AC_WID_PIN ||
	    (type == AC_WID_AUD_IN && codec->single_adc_amp)) अणु
		nums = 1;
		idx = 0;
	पूर्ण अन्यथा
		idx = path->idx[i];

	क्रम (n = 0; n < nums; n++)
		init_amp(codec, nid, HDA_INPUT, n);

	/* here is a little bit tricky in comparison with activate_amp_out();
	 * when aa-mixer is available, we need to enable the path as well
	 */
	क्रम (n = 0; n < nums; n++) अणु
		अगर (n != idx) अणु
			अगर (conn[n] != spec->mixer_merge_nid)
				जारी;
			/* when aamix is disabled, क्रमce to off */
			अगर (!add_aamix) अणु
				activate_amp(codec, nid, HDA_INPUT, n, n, false);
				जारी;
			पूर्ण
		पूर्ण
		check_and_activate_amp(codec, nid, HDA_INPUT, n, idx, enable);
	पूर्ण
पूर्ण

/* sync घातer of each widget in the given path */
अटल hda_nid_t path_घातer_update(काष्ठा hda_codec *codec,
				   काष्ठा nid_path *path,
				   bool allow_घातerकरोwn)
अणु
	hda_nid_t nid, changed = 0;
	पूर्णांक i, state, घातer;

	क्रम (i = 0; i < path->depth; i++) अणु
		nid = path->path[i];
		अगर (!(get_wcaps(codec, nid) & AC_WCAP_POWER))
			जारी;
		अगर (nid == codec->core.afg)
			जारी;
		अगर (!allow_घातerकरोwn || is_active_nid_क्रम_any(codec, nid))
			state = AC_PWRST_D0;
		अन्यथा
			state = AC_PWRST_D3;
		घातer = snd_hda_codec_पढ़ो(codec, nid, 0,
					   AC_VERB_GET_POWER_STATE, 0);
		अगर (घातer != (state | (state << 4))) अणु
			snd_hda_codec_ग_लिखो(codec, nid, 0,
					    AC_VERB_SET_POWER_STATE, state);
			changed = nid;
			/* all known codecs seem to be capable to handl
			 * widमाला_लो state even in D3, so far.
			 * अगर any new codecs need to restore the widget
			 * states after D0 transition, call the function
			 * below.
			 */
#अगर 0 /* disabled */
			अगर (state == AC_PWRST_D0)
				snd_hdac_regmap_sync_node(&codec->core, nid);
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	वापस changed;
पूर्ण

/* करो sync with the last घातer state change */
अटल व्योम sync_घातer_state_change(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अगर (nid) अणु
		msleep(10);
		snd_hda_codec_पढ़ो(codec, nid, 0, AC_VERB_GET_POWER_STATE, 0);
	पूर्ण
पूर्ण

/**
 * snd_hda_activate_path - activate or deactivate the given path
 * @codec: the HDA codec
 * @path: the path to activate/deactivate
 * @enable: flag to activate or not
 * @add_aamix: enable the input from aamix NID
 *
 * If @add_aamix is set, enable the input from aa-mix NID as well (अगर any).
 */
व्योम snd_hda_activate_path(काष्ठा hda_codec *codec, काष्ठा nid_path *path,
			   bool enable, bool add_aamix)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i;

	path->active = enable;

	/* make sure the widget is घातered up */
	अगर (enable && (spec->घातer_करोwn_unused || codec->घातer_save_node))
		path_घातer_update(codec, path, codec->घातer_save_node);

	क्रम (i = path->depth - 1; i >= 0; i--) अणु
		hda_nid_t nid = path->path[i];

		अगर (enable && path->multi[i])
			snd_hda_codec_ग_लिखो_cache(codec, nid, 0,
					    AC_VERB_SET_CONNECT_SEL,
					    path->idx[i]);
		अगर (has_amp_in(codec, path, i))
			activate_amp_in(codec, path, i, enable, add_aamix);
		अगर (has_amp_out(codec, path, i))
			activate_amp_out(codec, path, i, enable);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_activate_path);

/* अगर the given path is inactive, put widमाला_लो पूर्णांकo D3 (only अगर suitable) */
अटल व्योम path_घातer_करोwn_sync(काष्ठा hda_codec *codec, काष्ठा nid_path *path)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;

	अगर (!(spec->घातer_करोwn_unused || codec->घातer_save_node) || path->active)
		वापस;
	sync_घातer_state_change(codec, path_घातer_update(codec, path, true));
पूर्ण

/* turn on/off EAPD on the given pin */
अटल व्योम set_pin_eapd(काष्ठा hda_codec *codec, hda_nid_t pin, bool enable)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	अगर (spec->own_eapd_ctl ||
	    !(snd_hda_query_pin_caps(codec, pin) & AC_PINCAP_EAPD))
		वापस;
	अगर (spec->keep_eapd_on && !enable)
		वापस;
	अगर (codec->inv_eapd)
		enable = !enable;
	snd_hda_codec_ग_लिखो_cache(codec, pin, 0,
				   AC_VERB_SET_EAPD_BTLENABLE,
				   enable ? 0x02 : 0x00);
पूर्ण

/* re-initialize the path specअगरied by the given path index */
अटल व्योम resume_path_from_idx(काष्ठा hda_codec *codec, पूर्णांक path_idx)
अणु
	काष्ठा nid_path *path = snd_hda_get_path_from_idx(codec, path_idx);
	अगर (path)
		snd_hda_activate_path(codec, path, path->active, false);
पूर्ण


/*
 * Helper functions क्रम creating mixer ctl elements
 */

अटल पूर्णांक hda_gen_mixer_mute_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol);
अटल पूर्णांक hda_gen_bind_mute_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol);
अटल पूर्णांक hda_gen_bind_mute_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol);

क्रमागत अणु
	HDA_CTL_WIDGET_VOL,
	HDA_CTL_WIDGET_MUTE,
	HDA_CTL_BIND_MUTE,
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new control_ढाँचाs[] = अणु
	HDA_CODEC_VOLUME(शून्य, 0, 0, 0),
	/* only the put callback is replaced क्रम handling the special mute */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.subdevice = HDA_SUBDEV_AMP_FLAG,
		.info = snd_hda_mixer_amp_चयन_info,
		.get = snd_hda_mixer_amp_चयन_get,
		.put = hda_gen_mixer_mute_put, /* replaced */
		.निजी_value = HDA_COMPOSE_AMP_VAL(0, 3, 0, 0),
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.info = snd_hda_mixer_amp_चयन_info,
		.get = hda_gen_bind_mute_get,
		.put = hda_gen_bind_mute_put, /* replaced */
		.निजी_value = HDA_COMPOSE_AMP_VAL(0, 3, 0, 0),
	पूर्ण,
पूर्ण;

/* add dynamic controls from ढाँचा */
अटल काष्ठा snd_kcontrol_new *
add_control(काष्ठा hda_gen_spec *spec, पूर्णांक type, स्थिर अक्षर *name,
		       पूर्णांक cidx, अचिन्हित दीर्घ val)
अणु
	काष्ठा snd_kcontrol_new *knew;

	knew = snd_hda_gen_add_kctl(spec, name, &control_ढाँचाs[type]);
	अगर (!knew)
		वापस शून्य;
	knew->index = cidx;
	अगर (get_amp_nid_(val))
		knew->subdevice = HDA_SUBDEV_AMP_FLAG;
	अगर (knew->access == 0)
		knew->access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	knew->निजी_value = val;
	वापस knew;
पूर्ण

अटल पूर्णांक add_control_with_pfx(काष्ठा hda_gen_spec *spec, पूर्णांक type,
				स्थिर अक्षर *pfx, स्थिर अक्षर *dir,
				स्थिर अक्षर *sfx, पूर्णांक cidx, अचिन्हित दीर्घ val)
अणु
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	snम_लिखो(name, माप(name), "%s %s %s", pfx, dir, sfx);
	अगर (!add_control(spec, type, name, cidx, val))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

#घोषणा add_pb_vol_ctrl(spec, type, pfx, val)			\
	add_control_with_pfx(spec, type, pfx, "Playback", "Volume", 0, val)
#घोषणा add_pb_sw_ctrl(spec, type, pfx, val)			\
	add_control_with_pfx(spec, type, pfx, "Playback", "Switch", 0, val)
#घोषणा __add_pb_vol_ctrl(spec, type, pfx, cidx, val)			\
	add_control_with_pfx(spec, type, pfx, "Playback", "Volume", cidx, val)
#घोषणा __add_pb_sw_ctrl(spec, type, pfx, cidx, val)			\
	add_control_with_pfx(spec, type, pfx, "Playback", "Switch", cidx, val)

अटल पूर्णांक add_vol_ctl(काष्ठा hda_codec *codec, स्थिर अक्षर *pfx, पूर्णांक cidx,
		       अचिन्हित पूर्णांक chs, काष्ठा nid_path *path)
अणु
	अचिन्हित पूर्णांक val;
	अगर (!path)
		वापस 0;
	val = path->ctls[NID_PATH_VOL_CTL];
	अगर (!val)
		वापस 0;
	val = amp_val_replace_channels(val, chs);
	वापस __add_pb_vol_ctrl(codec->spec, HDA_CTL_WIDGET_VOL, pfx, cidx, val);
पूर्ण

/* वापस the channel bits suitable क्रम the given path->ctls[] */
अटल पूर्णांक get_शेष_ch_nums(काष्ठा hda_codec *codec, काष्ठा nid_path *path,
			       पूर्णांक type)
अणु
	पूर्णांक chs = 1; /* mono (left only) */
	अगर (path) अणु
		hda_nid_t nid = get_amp_nid_(path->ctls[type]);
		अगर (nid && (get_wcaps(codec, nid) & AC_WCAP_STEREO))
			chs = 3; /* stereo */
	पूर्ण
	वापस chs;
पूर्ण

अटल पूर्णांक add_stereo_vol(काष्ठा hda_codec *codec, स्थिर अक्षर *pfx, पूर्णांक cidx,
			  काष्ठा nid_path *path)
अणु
	पूर्णांक chs = get_शेष_ch_nums(codec, path, NID_PATH_VOL_CTL);
	वापस add_vol_ctl(codec, pfx, cidx, chs, path);
पूर्ण

/* create a mute-चयन क्रम the given mixer widget;
 * अगर it has multiple sources (e.g. DAC and loopback), create a bind-mute
 */
अटल पूर्णांक add_sw_ctl(काष्ठा hda_codec *codec, स्थिर अक्षर *pfx, पूर्णांक cidx,
		      अचिन्हित पूर्णांक chs, काष्ठा nid_path *path)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक type = HDA_CTL_WIDGET_MUTE;

	अगर (!path)
		वापस 0;
	val = path->ctls[NID_PATH_MUTE_CTL];
	अगर (!val)
		वापस 0;
	val = amp_val_replace_channels(val, chs);
	अगर (get_amp_direction_(val) == HDA_INPUT) अणु
		hda_nid_t nid = get_amp_nid_(val);
		पूर्णांक nums = snd_hda_get_num_conns(codec, nid);
		अगर (nums > 1) अणु
			type = HDA_CTL_BIND_MUTE;
			val |= nums << 19;
		पूर्ण
	पूर्ण
	वापस __add_pb_sw_ctrl(codec->spec, type, pfx, cidx, val);
पूर्ण

अटल पूर्णांक add_stereo_sw(काष्ठा hda_codec *codec, स्थिर अक्षर *pfx,
				  पूर्णांक cidx, काष्ठा nid_path *path)
अणु
	पूर्णांक chs = get_शेष_ch_nums(codec, path, NID_PATH_MUTE_CTL);
	वापस add_sw_ctl(codec, pfx, cidx, chs, path);
पूर्ण

/* playback mute control with the software mute bit check */
अटल व्योम sync_स्वतः_mute_bits(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;

	अगर (spec->स्वतः_mute_via_amp) अणु
		hda_nid_t nid = get_amp_nid(kcontrol);
		bool enabled = !((spec->mute_bits >> nid) & 1);
		ucontrol->value.पूर्णांकeger.value[0] &= enabled;
		ucontrol->value.पूर्णांकeger.value[1] &= enabled;
	पूर्ण
पूर्ण

अटल पूर्णांक hda_gen_mixer_mute_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	sync_स्वतः_mute_bits(kcontrol, ucontrol);
	वापस snd_hda_mixer_amp_चयन_put(kcontrol, ucontrol);
पूर्ण

/*
 * Bound mute controls
 */
#घोषणा AMP_VAL_IDX_SHIFT	19
#घोषणा AMP_VAL_IDX_MASK	(0x0f<<19)

अटल पूर्णांक hda_gen_bind_mute_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ pval;
	पूर्णांक err;

	mutex_lock(&codec->control_mutex);
	pval = kcontrol->निजी_value;
	kcontrol->निजी_value = pval & ~AMP_VAL_IDX_MASK; /* index 0 */
	err = snd_hda_mixer_amp_चयन_get(kcontrol, ucontrol);
	kcontrol->निजी_value = pval;
	mutex_unlock(&codec->control_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक hda_gen_bind_mute_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ pval;
	पूर्णांक i, indices, err = 0, change = 0;

	sync_स्वतः_mute_bits(kcontrol, ucontrol);

	mutex_lock(&codec->control_mutex);
	pval = kcontrol->निजी_value;
	indices = (pval & AMP_VAL_IDX_MASK) >> AMP_VAL_IDX_SHIFT;
	क्रम (i = 0; i < indices; i++) अणु
		kcontrol->निजी_value = (pval & ~AMP_VAL_IDX_MASK) |
			(i << AMP_VAL_IDX_SHIFT);
		err = snd_hda_mixer_amp_चयन_put(kcontrol, ucontrol);
		अगर (err < 0)
			अवरोध;
		change |= err;
	पूर्ण
	kcontrol->निजी_value = pval;
	mutex_unlock(&codec->control_mutex);
	वापस err < 0 ? err : change;
पूर्ण

/* any ctl asचिन्हित to the path with the given index? */
अटल bool path_has_mixer(काष्ठा hda_codec *codec, पूर्णांक path_idx, पूर्णांक ctl_type)
अणु
	काष्ठा nid_path *path = snd_hda_get_path_from_idx(codec, path_idx);
	वापस path && path->ctls[ctl_type];
पूर्ण

अटल स्थिर अक्षर * स्थिर channel_name[4] = अणु
	"Front", "Surround", "CLFE", "Side"
पूर्ण;

/* give some appropriate ctl name prefix क्रम the given line out channel */
अटल स्थिर अक्षर *get_line_out_pfx(काष्ठा hda_codec *codec, पूर्णांक ch,
				    पूर्णांक *index, पूर्णांक ctl_type)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;

	*index = 0;
	अगर (cfg->line_outs == 1 && !spec->multi_ios &&
	    !codec->क्रमce_pin_prefix &&
	    !cfg->hp_outs && !cfg->speaker_outs)
		वापस spec->vmaster_mute.hook ? "PCM" : "Master";

	/* अगर there is really a single DAC used in the whole output paths,
	 * use it master (or "PCM" अगर a vmaster hook is present)
	 */
	अगर (spec->multiout.num_dacs == 1 && !spec->mixer_nid &&
	    !codec->क्रमce_pin_prefix &&
	    !spec->multiout.hp_out_nid[0] && !spec->multiout.extra_out_nid[0])
		वापस spec->vmaster_mute.hook ? "PCM" : "Master";

	/* multi-io channels */
	अगर (ch >= cfg->line_outs)
		वापस channel_name[ch];

	चयन (cfg->line_out_type) अणु
	हाल AUTO_PIN_SPEAKER_OUT:
		/* अगर the primary channel vol/mute is shared with HP volume,
		 * करोn't name it as Speaker
		 */
		अगर (!ch && cfg->hp_outs &&
		    !path_has_mixer(codec, spec->hp_paths[0], ctl_type))
			अवरोध;
		अगर (cfg->line_outs == 1)
			वापस "Speaker";
		अगर (cfg->line_outs == 2)
			वापस ch ? "Bass Speaker" : "Speaker";
		अवरोध;
	हाल AUTO_PIN_HP_OUT:
		/* अगर the primary channel vol/mute is shared with spk volume,
		 * करोn't name it as Headphone
		 */
		अगर (!ch && cfg->speaker_outs &&
		    !path_has_mixer(codec, spec->speaker_paths[0], ctl_type))
			अवरोध;
		/* क्रम multi-io हाल, only the primary out */
		अगर (ch && spec->multi_ios)
			अवरोध;
		*index = ch;
		वापस "Headphone";
	हाल AUTO_PIN_LINE_OUT:
		/* This deals with the हाल where one HP or one Speaker or
		 * one HP + one Speaker need to share the DAC with LO
		 */
		अगर (!ch) अणु
			bool hp_lo_shared = false, spk_lo_shared = false;

			अगर (cfg->speaker_outs)
				spk_lo_shared = !path_has_mixer(codec,
								spec->speaker_paths[0],	ctl_type);
			अगर (cfg->hp_outs)
				hp_lo_shared = !path_has_mixer(codec, spec->hp_paths[0], ctl_type);
			अगर (hp_lo_shared && spk_lo_shared)
				वापस spec->vmaster_mute.hook ? "PCM" : "Master";
			अगर (hp_lo_shared)
				वापस "Headphone+LO";
			अगर (spk_lo_shared)
				वापस "Speaker+LO";
		पूर्ण
	पूर्ण

	/* क्रम a single channel output, we करोn't have to name the channel */
	अगर (cfg->line_outs == 1 && !spec->multi_ios)
		वापस "Line Out";

	अगर (ch >= ARRAY_SIZE(channel_name)) अणु
		snd_BUG();
		वापस "PCM";
	पूर्ण

	वापस channel_name[ch];
पूर्ण

/*
 * Parse output paths
 */

/* badness definition */
क्रमागत अणु
	/* No primary DAC is found क्रम the मुख्य output */
	BAD_NO_PRIMARY_DAC = 0x10000,
	/* No DAC is found क्रम the extra output */
	BAD_NO_DAC = 0x4000,
	/* No possible multi-ios */
	BAD_MULTI_IO = 0x120,
	/* No inभागidual DAC क्रम extra output */
	BAD_NO_EXTRA_DAC = 0x102,
	/* No inभागidual DAC क्रम extra surrounds */
	BAD_NO_EXTRA_SURR_DAC = 0x101,
	/* Primary DAC shared with मुख्य surrounds */
	BAD_SHARED_SURROUND = 0x100,
	/* No independent HP possible */
	BAD_NO_INDEP_HP = 0x10,
	/* Primary DAC shared with मुख्य CLFE */
	BAD_SHARED_CLFE = 0x10,
	/* Primary DAC shared with extra surrounds */
	BAD_SHARED_EXTRA_SURROUND = 0x10,
	/* Volume widget is shared */
	BAD_SHARED_VOL = 0x10,
पूर्ण;

/* look क्रम widमाला_लो in the given path which are appropriate क्रम
 * volume and mute controls, and assign the values to ctls[].
 *
 * When no appropriate widget is found in the path, the badness value
 * is incremented depending on the situation.  The function वापसs the
 * total badness क्रम both volume and mute controls.
 */
अटल पूर्णांक assign_out_path_ctls(काष्ठा hda_codec *codec, काष्ठा nid_path *path)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	hda_nid_t nid;
	अचिन्हित पूर्णांक val;
	पूर्णांक badness = 0;

	अगर (!path)
		वापस BAD_SHARED_VOL * 2;

	अगर (path->ctls[NID_PATH_VOL_CTL] ||
	    path->ctls[NID_PATH_MUTE_CTL])
		वापस 0; /* alपढ़ोy evaluated */

	nid = look_क्रम_out_vol_nid(codec, path);
	अगर (nid) अणु
		val = HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_OUTPUT);
		अगर (spec->dac_min_mute)
			val |= HDA_AMP_VAL_MIN_MUTE;
		अगर (is_ctl_used(codec, val, NID_PATH_VOL_CTL))
			badness += BAD_SHARED_VOL;
		अन्यथा
			path->ctls[NID_PATH_VOL_CTL] = val;
	पूर्ण अन्यथा
		badness += BAD_SHARED_VOL;
	nid = look_क्रम_out_mute_nid(codec, path);
	अगर (nid) अणु
		अचिन्हित पूर्णांक wid_type = get_wcaps_type(get_wcaps(codec, nid));
		अगर (wid_type == AC_WID_PIN || wid_type == AC_WID_AUD_OUT ||
		    nid_has_mute(codec, nid, HDA_OUTPUT))
			val = HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_OUTPUT);
		अन्यथा
			val = HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_INPUT);
		अगर (is_ctl_used(codec, val, NID_PATH_MUTE_CTL))
			badness += BAD_SHARED_VOL;
		अन्यथा
			path->ctls[NID_PATH_MUTE_CTL] = val;
	पूर्ण अन्यथा
		badness += BAD_SHARED_VOL;
	वापस badness;
पूर्ण

स्थिर काष्ठा badness_table hda_मुख्य_out_badness = अणु
	.no_primary_dac = BAD_NO_PRIMARY_DAC,
	.no_dac = BAD_NO_DAC,
	.shared_primary = BAD_NO_PRIMARY_DAC,
	.shared_surr = BAD_SHARED_SURROUND,
	.shared_clfe = BAD_SHARED_CLFE,
	.shared_surr_मुख्य = BAD_SHARED_SURROUND,
पूर्ण;
EXPORT_SYMBOL_GPL(hda_मुख्य_out_badness);

स्थिर काष्ठा badness_table hda_extra_out_badness = अणु
	.no_primary_dac = BAD_NO_DAC,
	.no_dac = BAD_NO_DAC,
	.shared_primary = BAD_NO_EXTRA_DAC,
	.shared_surr = BAD_SHARED_EXTRA_SURROUND,
	.shared_clfe = BAD_SHARED_EXTRA_SURROUND,
	.shared_surr_मुख्य = BAD_NO_EXTRA_SURR_DAC,
पूर्ण;
EXPORT_SYMBOL_GPL(hda_extra_out_badness);

/* get the DAC of the primary output corresponding to the given array index */
अटल hda_nid_t get_primary_out(काष्ठा hda_codec *codec, पूर्णांक idx)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;

	अगर (cfg->line_outs > idx)
		वापस spec->निजी_dac_nids[idx];
	idx -= cfg->line_outs;
	अगर (spec->multi_ios > idx)
		वापस spec->multi_io[idx].dac;
	वापस 0;
पूर्ण

/* वापस the DAC अगर it's reachable, otherwise zero */
अटल अंतरभूत hda_nid_t try_dac(काष्ठा hda_codec *codec,
				hda_nid_t dac, hda_nid_t pin)
अणु
	वापस is_reachable_path(codec, dac, pin) ? dac : 0;
पूर्ण

/* try to assign DACs to pins and वापस the resultant badness */
अटल पूर्णांक try_assign_dacs(काष्ठा hda_codec *codec, पूर्णांक num_outs,
			   स्थिर hda_nid_t *pins, hda_nid_t *dacs,
			   पूर्णांक *path_idx,
			   स्थिर काष्ठा badness_table *bad)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i, j;
	पूर्णांक badness = 0;
	hda_nid_t dac;

	अगर (!num_outs)
		वापस 0;

	क्रम (i = 0; i < num_outs; i++) अणु
		काष्ठा nid_path *path;
		hda_nid_t pin = pins[i];

		अगर (!spec->obey_preferred_dacs) अणु
			path = snd_hda_get_path_from_idx(codec, path_idx[i]);
			अगर (path) अणु
				badness += assign_out_path_ctls(codec, path);
				जारी;
			पूर्ण
		पूर्ण

		dacs[i] = get_preferred_dac(codec, pin);
		अगर (dacs[i]) अणु
			अगर (is_dac_alपढ़ोy_used(codec, dacs[i]))
				badness += bad->shared_primary;
		पूर्ण अन्यथा अगर (spec->obey_preferred_dacs) अणु
			badness += BAD_NO_PRIMARY_DAC;
		पूर्ण

		अगर (!dacs[i])
			dacs[i] = look_क्रम_dac(codec, pin, false);
		अगर (!dacs[i] && !i) अणु
			/* try to steal the DAC of surrounds क्रम the front */
			क्रम (j = 1; j < num_outs; j++) अणु
				अगर (is_reachable_path(codec, dacs[j], pin)) अणु
					dacs[0] = dacs[j];
					dacs[j] = 0;
					invalidate_nid_path(codec, path_idx[j]);
					path_idx[j] = 0;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		dac = dacs[i];
		अगर (!dac) अणु
			अगर (num_outs > 2)
				dac = try_dac(codec, get_primary_out(codec, i), pin);
			अगर (!dac)
				dac = try_dac(codec, dacs[0], pin);
			अगर (!dac)
				dac = try_dac(codec, get_primary_out(codec, i), pin);
			अगर (dac) अणु
				अगर (!i)
					badness += bad->shared_primary;
				अन्यथा अगर (i == 1)
					badness += bad->shared_surr;
				अन्यथा
					badness += bad->shared_clfe;
			पूर्ण अन्यथा अगर (is_reachable_path(codec, spec->निजी_dac_nids[0], pin)) अणु
				dac = spec->निजी_dac_nids[0];
				badness += bad->shared_surr_मुख्य;
			पूर्ण अन्यथा अगर (!i)
				badness += bad->no_primary_dac;
			अन्यथा
				badness += bad->no_dac;
		पूर्ण
		अगर (!dac)
			जारी;
		path = snd_hda_add_new_path(codec, dac, pin, -spec->mixer_nid);
		अगर (!path && !i && spec->mixer_nid) अणु
			/* try with aamix */
			path = snd_hda_add_new_path(codec, dac, pin, 0);
		पूर्ण
		अगर (!path) अणु
			dac = dacs[i] = 0;
			badness += bad->no_dac;
		पूर्ण अन्यथा अणु
			/* prपूर्णांक_nid_path(codec, "output", path); */
			path->active = true;
			path_idx[i] = snd_hda_get_path_idx(codec, path);
			badness += assign_out_path_ctls(codec, path);
		पूर्ण
	पूर्ण

	वापस badness;
पूर्ण

/* वापस NID अगर the given pin has only a single connection to a certain DAC */
अटल hda_nid_t get_dac_अगर_single(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i;
	hda_nid_t nid_found = 0;

	क्रम (i = 0; i < spec->num_all_dacs; i++) अणु
		hda_nid_t nid = spec->all_dacs[i];
		अगर (!nid || is_dac_alपढ़ोy_used(codec, nid))
			जारी;
		अगर (is_reachable_path(codec, nid, pin)) अणु
			अगर (nid_found)
				वापस 0;
			nid_found = nid;
		पूर्ण
	पूर्ण
	वापस nid_found;
पूर्ण

/* check whether the given pin can be a multi-io pin */
अटल bool can_be_multiio_pin(काष्ठा hda_codec *codec,
			       अचिन्हित पूर्णांक location, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक defcfg, caps;

	defcfg = snd_hda_codec_get_pincfg(codec, nid);
	अगर (get_defcfg_connect(defcfg) != AC_JACK_PORT_COMPLEX)
		वापस false;
	अगर (location && get_defcfg_location(defcfg) != location)
		वापस false;
	caps = snd_hda_query_pin_caps(codec, nid);
	अगर (!(caps & AC_PINCAP_OUT))
		वापस false;
	वापस true;
पूर्ण

/* count the number of input pins that are capable to be multi-io */
अटल पूर्णांक count_multiio_pins(काष्ठा hda_codec *codec, hda_nid_t reference_pin)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	अचिन्हित पूर्णांक defcfg = snd_hda_codec_get_pincfg(codec, reference_pin);
	अचिन्हित पूर्णांक location = get_defcfg_location(defcfg);
	पूर्णांक type, i;
	पूर्णांक num_pins = 0;

	क्रम (type = AUTO_PIN_LINE_IN; type >= AUTO_PIN_MIC; type--) अणु
		क्रम (i = 0; i < cfg->num_inमाला_दो; i++) अणु
			अगर (cfg->inमाला_दो[i].type != type)
				जारी;
			अगर (can_be_multiio_pin(codec, location,
					       cfg->inमाला_दो[i].pin))
				num_pins++;
		पूर्ण
	पूर्ण
	वापस num_pins;
पूर्ण

/*
 * multi-io helper
 *
 * When hardwired is set, try to fill ony hardwired pins, and वापसs
 * zero अगर any pins are filled, non-zero अगर nothing found.
 * When hardwired is off, try to fill possible input pins, and वापसs
 * the badness value.
 */
अटल पूर्णांक fill_multi_ios(काष्ठा hda_codec *codec,
			  hda_nid_t reference_pin,
			  bool hardwired)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	पूर्णांक type, i, j, num_pins, old_pins;
	अचिन्हित पूर्णांक defcfg = snd_hda_codec_get_pincfg(codec, reference_pin);
	अचिन्हित पूर्णांक location = get_defcfg_location(defcfg);
	पूर्णांक badness = 0;
	काष्ठा nid_path *path;

	old_pins = spec->multi_ios;
	अगर (old_pins >= 2)
		जाओ end_fill;

	num_pins = count_multiio_pins(codec, reference_pin);
	अगर (num_pins < 2)
		जाओ end_fill;

	क्रम (type = AUTO_PIN_LINE_IN; type >= AUTO_PIN_MIC; type--) अणु
		क्रम (i = 0; i < cfg->num_inमाला_दो; i++) अणु
			hda_nid_t nid = cfg->inमाला_दो[i].pin;
			hda_nid_t dac = 0;

			अगर (cfg->inमाला_दो[i].type != type)
				जारी;
			अगर (!can_be_multiio_pin(codec, location, nid))
				जारी;
			क्रम (j = 0; j < spec->multi_ios; j++) अणु
				अगर (nid == spec->multi_io[j].pin)
					अवरोध;
			पूर्ण
			अगर (j < spec->multi_ios)
				जारी;

			अगर (hardwired)
				dac = get_dac_अगर_single(codec, nid);
			अन्यथा अगर (!dac)
				dac = look_क्रम_dac(codec, nid, false);
			अगर (!dac) अणु
				badness++;
				जारी;
			पूर्ण
			path = snd_hda_add_new_path(codec, dac, nid,
						    -spec->mixer_nid);
			अगर (!path) अणु
				badness++;
				जारी;
			पूर्ण
			/* prपूर्णांक_nid_path(codec, "multiio", path); */
			spec->multi_io[spec->multi_ios].pin = nid;
			spec->multi_io[spec->multi_ios].dac = dac;
			spec->out_paths[cfg->line_outs + spec->multi_ios] =
				snd_hda_get_path_idx(codec, path);
			spec->multi_ios++;
			अगर (spec->multi_ios >= 2)
				अवरोध;
		पूर्ण
	पूर्ण
 end_fill:
	अगर (badness)
		badness = BAD_MULTI_IO;
	अगर (old_pins == spec->multi_ios) अणु
		अगर (hardwired)
			वापस 1; /* nothing found */
		अन्यथा
			वापस badness; /* no badness अगर nothing found */
	पूर्ण
	अगर (!hardwired && spec->multi_ios < 2) अणु
		/* cancel newly asचिन्हित paths */
		spec->paths.used -= spec->multi_ios - old_pins;
		spec->multi_ios = old_pins;
		वापस badness;
	पूर्ण

	/* assign volume and mute controls */
	क्रम (i = old_pins; i < spec->multi_ios; i++) अणु
		path = snd_hda_get_path_from_idx(codec, spec->out_paths[cfg->line_outs + i]);
		badness += assign_out_path_ctls(codec, path);
	पूर्ण

	वापस badness;
पूर्ण

/* map DACs क्रम all pins in the list अगर they are single connections */
अटल bool map_singles(काष्ठा hda_codec *codec, पूर्णांक outs,
			स्थिर hda_nid_t *pins, hda_nid_t *dacs, पूर्णांक *path_idx)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i;
	bool found = false;
	क्रम (i = 0; i < outs; i++) अणु
		काष्ठा nid_path *path;
		hda_nid_t dac;
		अगर (dacs[i])
			जारी;
		dac = get_dac_अगर_single(codec, pins[i]);
		अगर (!dac)
			जारी;
		path = snd_hda_add_new_path(codec, dac, pins[i],
					    -spec->mixer_nid);
		अगर (!path && !i && spec->mixer_nid)
			path = snd_hda_add_new_path(codec, dac, pins[i], 0);
		अगर (path) अणु
			dacs[i] = dac;
			found = true;
			/* prपूर्णांक_nid_path(codec, "output", path); */
			path->active = true;
			path_idx[i] = snd_hda_get_path_idx(codec, path);
		पूर्ण
	पूर्ण
	वापस found;
पूर्ण

अटल अंतरभूत bool has_aamix_out_paths(काष्ठा hda_gen_spec *spec)
अणु
	वापस spec->aamix_out_paths[0] || spec->aamix_out_paths[1] ||
		spec->aamix_out_paths[2];
पूर्ण

/* create a new path including aamix अगर available, and वापस its index */
अटल पूर्णांक check_aamix_out_path(काष्ठा hda_codec *codec, पूर्णांक path_idx)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा nid_path *path;
	hda_nid_t path_dac, dac, pin;

	path = snd_hda_get_path_from_idx(codec, path_idx);
	अगर (!path || !path->depth ||
	    is_nid_contained(path, spec->mixer_nid))
		वापस 0;
	path_dac = path->path[0];
	dac = spec->निजी_dac_nids[0];
	pin = path->path[path->depth - 1];
	path = snd_hda_add_new_path(codec, dac, pin, spec->mixer_nid);
	अगर (!path) अणु
		अगर (dac != path_dac)
			dac = path_dac;
		अन्यथा अगर (spec->multiout.hp_out_nid[0])
			dac = spec->multiout.hp_out_nid[0];
		अन्यथा अगर (spec->multiout.extra_out_nid[0])
			dac = spec->multiout.extra_out_nid[0];
		अन्यथा
			dac = 0;
		अगर (dac)
			path = snd_hda_add_new_path(codec, dac, pin,
						    spec->mixer_nid);
	पूर्ण
	अगर (!path)
		वापस 0;
	/* prपूर्णांक_nid_path(codec, "output-aamix", path); */
	path->active = false; /* unused as शेष */
	path->pin_fixed = true; /* अटल route */
	वापस snd_hda_get_path_idx(codec, path);
पूर्ण

/* check whether the independent HP is available with the current config */
अटल bool indep_hp_possible(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	काष्ठा nid_path *path;
	पूर्णांक i, idx;

	अगर (cfg->line_out_type == AUTO_PIN_HP_OUT)
		idx = spec->out_paths[0];
	अन्यथा
		idx = spec->hp_paths[0];
	path = snd_hda_get_path_from_idx(codec, idx);
	अगर (!path)
		वापस false;

	/* assume no path conflicts unless aamix is involved */
	अगर (!spec->mixer_nid || !is_nid_contained(path, spec->mixer_nid))
		वापस true;

	/* check whether output paths contain aamix */
	क्रम (i = 0; i < cfg->line_outs; i++) अणु
		अगर (spec->out_paths[i] == idx)
			अवरोध;
		path = snd_hda_get_path_from_idx(codec, spec->out_paths[i]);
		अगर (path && is_nid_contained(path, spec->mixer_nid))
			वापस false;
	पूर्ण
	क्रम (i = 0; i < cfg->speaker_outs; i++) अणु
		path = snd_hda_get_path_from_idx(codec, spec->speaker_paths[i]);
		अगर (path && is_nid_contained(path, spec->mixer_nid))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* fill the empty entries in the dac array क्रम speaker/hp with the
 * shared dac poपूर्णांकed by the paths
 */
अटल व्योम refill_shared_dacs(काष्ठा hda_codec *codec, पूर्णांक num_outs,
			       hda_nid_t *dacs, पूर्णांक *path_idx)
अणु
	काष्ठा nid_path *path;
	पूर्णांक i;

	क्रम (i = 0; i < num_outs; i++) अणु
		अगर (dacs[i])
			जारी;
		path = snd_hda_get_path_from_idx(codec, path_idx[i]);
		अगर (!path)
			जारी;
		dacs[i] = path->path[0];
	पूर्ण
पूर्ण

/* fill in the dac_nids table from the parsed pin configuration */
अटल पूर्णांक fill_and_eval_dacs(काष्ठा hda_codec *codec,
			      bool fill_hardwired,
			      bool fill_mio_first)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	पूर्णांक i, err, badness;

	/* set num_dacs once to full क्रम look_क्रम_dac() */
	spec->multiout.num_dacs = cfg->line_outs;
	spec->multiout.dac_nids = spec->निजी_dac_nids;
	स_रखो(spec->निजी_dac_nids, 0, माप(spec->निजी_dac_nids));
	स_रखो(spec->multiout.hp_out_nid, 0, माप(spec->multiout.hp_out_nid));
	स_रखो(spec->multiout.extra_out_nid, 0, माप(spec->multiout.extra_out_nid));
	spec->multi_ios = 0;
	snd_array_मुक्त(&spec->paths);

	/* clear path indices */
	स_रखो(spec->out_paths, 0, माप(spec->out_paths));
	स_रखो(spec->hp_paths, 0, माप(spec->hp_paths));
	स_रखो(spec->speaker_paths, 0, माप(spec->speaker_paths));
	स_रखो(spec->aamix_out_paths, 0, माप(spec->aamix_out_paths));
	स_रखो(spec->digout_paths, 0, माप(spec->digout_paths));
	स_रखो(spec->input_paths, 0, माप(spec->input_paths));
	स_रखो(spec->loopback_paths, 0, माप(spec->loopback_paths));
	स_रखो(&spec->digin_path, 0, माप(spec->digin_path));

	badness = 0;

	/* fill hard-wired DACs first */
	अगर (fill_hardwired) अणु
		bool mapped;
		करो अणु
			mapped = map_singles(codec, cfg->line_outs,
					     cfg->line_out_pins,
					     spec->निजी_dac_nids,
					     spec->out_paths);
			mapped |= map_singles(codec, cfg->hp_outs,
					      cfg->hp_pins,
					      spec->multiout.hp_out_nid,
					      spec->hp_paths);
			mapped |= map_singles(codec, cfg->speaker_outs,
					      cfg->speaker_pins,
					      spec->multiout.extra_out_nid,
					      spec->speaker_paths);
			अगर (!spec->no_multi_io &&
			    fill_mio_first && cfg->line_outs == 1 &&
			    cfg->line_out_type != AUTO_PIN_SPEAKER_OUT) अणु
				err = fill_multi_ios(codec, cfg->line_out_pins[0], true);
				अगर (!err)
					mapped = true;
			पूर्ण
		पूर्ण जबतक (mapped);
	पूर्ण

	badness += try_assign_dacs(codec, cfg->line_outs, cfg->line_out_pins,
				   spec->निजी_dac_nids, spec->out_paths,
				   spec->मुख्य_out_badness);

	अगर (!spec->no_multi_io && fill_mio_first &&
	    cfg->line_outs == 1 && cfg->line_out_type != AUTO_PIN_SPEAKER_OUT) अणु
		/* try to fill multi-io first */
		err = fill_multi_ios(codec, cfg->line_out_pins[0], false);
		अगर (err < 0)
			वापस err;
		/* we करोn't count badness at this stage yet */
	पूर्ण

	अगर (cfg->line_out_type != AUTO_PIN_HP_OUT) अणु
		err = try_assign_dacs(codec, cfg->hp_outs, cfg->hp_pins,
				      spec->multiout.hp_out_nid,
				      spec->hp_paths,
				      spec->extra_out_badness);
		अगर (err < 0)
			वापस err;
		badness += err;
	पूर्ण
	अगर (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT) अणु
		err = try_assign_dacs(codec, cfg->speaker_outs,
				      cfg->speaker_pins,
				      spec->multiout.extra_out_nid,
				      spec->speaker_paths,
				      spec->extra_out_badness);
		अगर (err < 0)
			वापस err;
		badness += err;
	पूर्ण
	अगर (!spec->no_multi_io &&
	    cfg->line_outs == 1 && cfg->line_out_type != AUTO_PIN_SPEAKER_OUT) अणु
		err = fill_multi_ios(codec, cfg->line_out_pins[0], false);
		अगर (err < 0)
			वापस err;
		badness += err;
	पूर्ण

	अगर (spec->mixer_nid) अणु
		spec->aamix_out_paths[0] =
			check_aamix_out_path(codec, spec->out_paths[0]);
		अगर (cfg->line_out_type != AUTO_PIN_HP_OUT)
			spec->aamix_out_paths[1] =
				check_aamix_out_path(codec, spec->hp_paths[0]);
		अगर (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT)
			spec->aamix_out_paths[2] =
				check_aamix_out_path(codec, spec->speaker_paths[0]);
	पूर्ण

	अगर (!spec->no_multi_io &&
	    cfg->hp_outs && cfg->line_out_type == AUTO_PIN_SPEAKER_OUT)
		अगर (count_multiio_pins(codec, cfg->hp_pins[0]) >= 2)
			spec->multi_ios = 1; /* give badness */

	/* re-count num_dacs and squash invalid entries */
	spec->multiout.num_dacs = 0;
	क्रम (i = 0; i < cfg->line_outs; i++) अणु
		अगर (spec->निजी_dac_nids[i])
			spec->multiout.num_dacs++;
		अन्यथा अणु
			स_हटाओ(spec->निजी_dac_nids + i,
				spec->निजी_dac_nids + i + 1,
				माप(hda_nid_t) * (cfg->line_outs - i - 1));
			spec->निजी_dac_nids[cfg->line_outs - 1] = 0;
		पूर्ण
	पूर्ण

	spec->ext_channel_count = spec->min_channel_count =
		spec->multiout.num_dacs * 2;

	अगर (spec->multi_ios == 2) अणु
		क्रम (i = 0; i < 2; i++)
			spec->निजी_dac_nids[spec->multiout.num_dacs++] =
				spec->multi_io[i].dac;
	पूर्ण अन्यथा अगर (spec->multi_ios) अणु
		spec->multi_ios = 0;
		badness += BAD_MULTI_IO;
	पूर्ण

	अगर (spec->indep_hp && !indep_hp_possible(codec))
		badness += BAD_NO_INDEP_HP;

	/* re-fill the shared DAC क्रम speaker / headphone */
	अगर (cfg->line_out_type != AUTO_PIN_HP_OUT)
		refill_shared_dacs(codec, cfg->hp_outs,
				   spec->multiout.hp_out_nid,
				   spec->hp_paths);
	अगर (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT)
		refill_shared_dacs(codec, cfg->speaker_outs,
				   spec->multiout.extra_out_nid,
				   spec->speaker_paths);

	वापस badness;
पूर्ण

#घोषणा DEBUG_BADNESS

#अगर_घोषित DEBUG_BADNESS
#घोषणा debug_badness(fmt, ...)						\
	codec_dbg(codec, fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा debug_badness(fmt, ...)						\
	करो अणु अगर (0) codec_dbg(codec, fmt, ##__VA_ARGS__); पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित DEBUG_BADNESS
अटल अंतरभूत व्योम prपूर्णांक_nid_path_idx(काष्ठा hda_codec *codec,
				      स्थिर अक्षर *pfx, पूर्णांक idx)
अणु
	काष्ठा nid_path *path;

	path = snd_hda_get_path_from_idx(codec, idx);
	अगर (path)
		prपूर्णांक_nid_path(codec, pfx, path);
पूर्ण

अटल व्योम debug_show_configs(काष्ठा hda_codec *codec,
			       काष्ठा स्वतः_pin_cfg *cfg)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	अटल स्थिर अक्षर * स्थिर lo_type[3] = अणु "LO", "SP", "HP" पूर्ण;
	पूर्णांक i;

	debug_badness("multi_outs = %x/%x/%x/%x : %x/%x/%x/%x (type %s)\n",
		      cfg->line_out_pins[0], cfg->line_out_pins[1],
		      cfg->line_out_pins[2], cfg->line_out_pins[3],
		      spec->multiout.dac_nids[0],
		      spec->multiout.dac_nids[1],
		      spec->multiout.dac_nids[2],
		      spec->multiout.dac_nids[3],
		      lo_type[cfg->line_out_type]);
	क्रम (i = 0; i < cfg->line_outs; i++)
		prपूर्णांक_nid_path_idx(codec, "  out", spec->out_paths[i]);
	अगर (spec->multi_ios > 0)
		debug_badness("multi_ios(%d) = %x/%x : %x/%x\n",
			      spec->multi_ios,
			      spec->multi_io[0].pin, spec->multi_io[1].pin,
			      spec->multi_io[0].dac, spec->multi_io[1].dac);
	क्रम (i = 0; i < spec->multi_ios; i++)
		prपूर्णांक_nid_path_idx(codec, "  mio",
				   spec->out_paths[cfg->line_outs + i]);
	अगर (cfg->hp_outs)
		debug_badness("hp_outs = %x/%x/%x/%x : %x/%x/%x/%x\n",
		      cfg->hp_pins[0], cfg->hp_pins[1],
		      cfg->hp_pins[2], cfg->hp_pins[3],
		      spec->multiout.hp_out_nid[0],
		      spec->multiout.hp_out_nid[1],
		      spec->multiout.hp_out_nid[2],
		      spec->multiout.hp_out_nid[3]);
	क्रम (i = 0; i < cfg->hp_outs; i++)
		prपूर्णांक_nid_path_idx(codec, "  hp ", spec->hp_paths[i]);
	अगर (cfg->speaker_outs)
		debug_badness("spk_outs = %x/%x/%x/%x : %x/%x/%x/%x\n",
		      cfg->speaker_pins[0], cfg->speaker_pins[1],
		      cfg->speaker_pins[2], cfg->speaker_pins[3],
		      spec->multiout.extra_out_nid[0],
		      spec->multiout.extra_out_nid[1],
		      spec->multiout.extra_out_nid[2],
		      spec->multiout.extra_out_nid[3]);
	क्रम (i = 0; i < cfg->speaker_outs; i++)
		prपूर्णांक_nid_path_idx(codec, "  spk", spec->speaker_paths[i]);
	क्रम (i = 0; i < 3; i++)
		prपूर्णांक_nid_path_idx(codec, "  mix", spec->aamix_out_paths[i]);
पूर्ण
#अन्यथा
#घोषणा debug_show_configs(codec, cfg) /* NOP */
#पूर्ण_अगर

/* find all available DACs of the codec */
अटल व्योम fill_all_dac_nids(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	hda_nid_t nid;

	spec->num_all_dacs = 0;
	स_रखो(spec->all_dacs, 0, माप(spec->all_dacs));
	क्रम_each_hda_codec_node(nid, codec) अणु
		अगर (get_wcaps_type(get_wcaps(codec, nid)) != AC_WID_AUD_OUT)
			जारी;
		अगर (spec->num_all_dacs >= ARRAY_SIZE(spec->all_dacs)) अणु
			codec_err(codec, "Too many DACs!\n");
			अवरोध;
		पूर्ण
		spec->all_dacs[spec->num_all_dacs++] = nid;
	पूर्ण
पूर्ण

अटल पूर्णांक parse_output_paths(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	काष्ठा स्वतः_pin_cfg *best_cfg;
	अचिन्हित पूर्णांक val;
	पूर्णांक best_badness = पूर्णांक_उच्च;
	पूर्णांक badness;
	bool fill_hardwired = true, fill_mio_first = true;
	bool best_wired = true, best_mio = true;
	bool hp_spk_swapped = false;

	best_cfg = kदो_स्मृति(माप(*best_cfg), GFP_KERNEL);
	अगर (!best_cfg)
		वापस -ENOMEM;
	*best_cfg = *cfg;

	क्रम (;;) अणु
		badness = fill_and_eval_dacs(codec, fill_hardwired,
					     fill_mio_first);
		अगर (badness < 0) अणु
			kमुक्त(best_cfg);
			वापस badness;
		पूर्ण
		debug_badness("==> lo_type=%d, wired=%d, mio=%d, badness=0x%x\n",
			      cfg->line_out_type, fill_hardwired, fill_mio_first,
			      badness);
		debug_show_configs(codec, cfg);
		अगर (badness < best_badness) अणु
			best_badness = badness;
			*best_cfg = *cfg;
			best_wired = fill_hardwired;
			best_mio = fill_mio_first;
		पूर्ण
		अगर (!badness)
			अवरोध;
		fill_mio_first = !fill_mio_first;
		अगर (!fill_mio_first)
			जारी;
		fill_hardwired = !fill_hardwired;
		अगर (!fill_hardwired)
			जारी;
		अगर (hp_spk_swapped)
			अवरोध;
		hp_spk_swapped = true;
		अगर (cfg->speaker_outs > 0 &&
		    cfg->line_out_type == AUTO_PIN_HP_OUT) अणु
			cfg->hp_outs = cfg->line_outs;
			स_नकल(cfg->hp_pins, cfg->line_out_pins,
			       माप(cfg->hp_pins));
			cfg->line_outs = cfg->speaker_outs;
			स_नकल(cfg->line_out_pins, cfg->speaker_pins,
			       माप(cfg->speaker_pins));
			cfg->speaker_outs = 0;
			स_रखो(cfg->speaker_pins, 0, माप(cfg->speaker_pins));
			cfg->line_out_type = AUTO_PIN_SPEAKER_OUT;
			fill_hardwired = true;
			जारी;
		पूर्ण
		अगर (cfg->hp_outs > 0 &&
		    cfg->line_out_type == AUTO_PIN_SPEAKER_OUT) अणु
			cfg->speaker_outs = cfg->line_outs;
			स_नकल(cfg->speaker_pins, cfg->line_out_pins,
			       माप(cfg->speaker_pins));
			cfg->line_outs = cfg->hp_outs;
			स_नकल(cfg->line_out_pins, cfg->hp_pins,
			       माप(cfg->hp_pins));
			cfg->hp_outs = 0;
			स_रखो(cfg->hp_pins, 0, माप(cfg->hp_pins));
			cfg->line_out_type = AUTO_PIN_HP_OUT;
			fill_hardwired = true;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (badness) अणु
		debug_badness("==> restoring best_cfg\n");
		*cfg = *best_cfg;
		fill_and_eval_dacs(codec, best_wired, best_mio);
	पूर्ण
	debug_badness("==> Best config: lo_type=%d, wired=%d, mio=%d\n",
		      cfg->line_out_type, best_wired, best_mio);
	debug_show_configs(codec, cfg);

	अगर (cfg->line_out_pins[0]) अणु
		काष्ठा nid_path *path;
		path = snd_hda_get_path_from_idx(codec, spec->out_paths[0]);
		अगर (path)
			spec->vmaster_nid = look_क्रम_out_vol_nid(codec, path);
		अगर (spec->vmaster_nid) अणु
			snd_hda_set_vmaster_tlv(codec, spec->vmaster_nid,
						HDA_OUTPUT, spec->vmaster_tlv);
			अगर (spec->dac_min_mute)
				spec->vmaster_tlv[SNDRV_CTL_TLVO_DB_SCALE_MUTE_AND_STEP] |= TLV_DB_SCALE_MUTE;
		पूर्ण
	पूर्ण

	/* set initial pinctl tarमाला_लो */
	अगर (spec->prefer_hp_amp || cfg->line_out_type == AUTO_PIN_HP_OUT)
		val = PIN_HP;
	अन्यथा
		val = PIN_OUT;
	set_pin_tarमाला_लो(codec, cfg->line_outs, cfg->line_out_pins, val);
	अगर (cfg->line_out_type != AUTO_PIN_HP_OUT)
		set_pin_tarमाला_लो(codec, cfg->hp_outs, cfg->hp_pins, PIN_HP);
	अगर (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT) अणु
		val = spec->prefer_hp_amp ? PIN_HP : PIN_OUT;
		set_pin_tarमाला_लो(codec, cfg->speaker_outs,
				cfg->speaker_pins, val);
	पूर्ण

	/* clear indep_hp flag अगर not available */
	अगर (spec->indep_hp && !indep_hp_possible(codec))
		spec->indep_hp = 0;

	kमुक्त(best_cfg);
	वापस 0;
पूर्ण

/* add playback controls from the parsed DAC table */
अटल पूर्णांक create_multi_out_ctls(काष्ठा hda_codec *codec,
				 स्थिर काष्ठा स्वतः_pin_cfg *cfg)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i, err, noutमाला_दो;

	noutमाला_दो = cfg->line_outs;
	अगर (spec->multi_ios > 0 && cfg->line_outs < 3)
		noutमाला_दो += spec->multi_ios;

	क्रम (i = 0; i < noutमाला_दो; i++) अणु
		स्थिर अक्षर *name;
		पूर्णांक index;
		काष्ठा nid_path *path;

		path = snd_hda_get_path_from_idx(codec, spec->out_paths[i]);
		अगर (!path)
			जारी;

		name = get_line_out_pfx(codec, i, &index, NID_PATH_VOL_CTL);
		अगर (!name || !म_भेद(name, "CLFE")) अणु
			/* Center/LFE */
			err = add_vol_ctl(codec, "Center", 0, 1, path);
			अगर (err < 0)
				वापस err;
			err = add_vol_ctl(codec, "LFE", 0, 2, path);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			err = add_stereo_vol(codec, name, index, path);
			अगर (err < 0)
				वापस err;
		पूर्ण

		name = get_line_out_pfx(codec, i, &index, NID_PATH_MUTE_CTL);
		अगर (!name || !म_भेद(name, "CLFE")) अणु
			err = add_sw_ctl(codec, "Center", 0, 1, path);
			अगर (err < 0)
				वापस err;
			err = add_sw_ctl(codec, "LFE", 0, 2, path);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			err = add_stereo_sw(codec, name, index, path);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक create_extra_out(काष्ठा hda_codec *codec, पूर्णांक path_idx,
			    स्थिर अक्षर *pfx, पूर्णांक cidx)
अणु
	काष्ठा nid_path *path;
	पूर्णांक err;

	path = snd_hda_get_path_from_idx(codec, path_idx);
	अगर (!path)
		वापस 0;
	err = add_stereo_vol(codec, pfx, cidx, path);
	अगर (err < 0)
		वापस err;
	err = add_stereo_sw(codec, pfx, cidx, path);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

/* add playback controls क्रम speaker and HP outमाला_दो */
अटल पूर्णांक create_extra_outs(काष्ठा hda_codec *codec, पूर्णांक num_pins,
			     स्थिर पूर्णांक *paths, स्थिर अक्षर *pfx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_pins; i++) अणु
		स्थिर अक्षर *name;
		अक्षर पंचांगp[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
		पूर्णांक err, idx = 0;

		अगर (num_pins == 2 && i == 1 && !म_भेद(pfx, "Speaker"))
			name = "Bass Speaker";
		अन्यथा अगर (num_pins >= 3) अणु
			snम_लिखो(पंचांगp, माप(पंचांगp), "%s %s",
				 pfx, channel_name[i]);
			name = पंचांगp;
		पूर्ण अन्यथा अणु
			name = pfx;
			idx = i;
		पूर्ण
		err = create_extra_out(codec, paths[i], name, idx);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक create_hp_out_ctls(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	वापस create_extra_outs(codec, spec->स्वतःcfg.hp_outs,
				 spec->hp_paths,
				 "Headphone");
पूर्ण

अटल पूर्णांक create_speaker_out_ctls(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	वापस create_extra_outs(codec, spec->स्वतःcfg.speaker_outs,
				 spec->speaker_paths,
				 "Speaker");
पूर्ण

/*
 * independent HP controls
 */

अटल व्योम call_hp_स्वतःmute(काष्ठा hda_codec *codec,
			     काष्ठा hda_jack_callback *jack);
अटल पूर्णांक indep_hp_info(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	वापस snd_hda_क्रमागत_bool_helper_info(kcontrol, uinfo);
पूर्ण

अटल पूर्णांक indep_hp_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	ucontrol->value.क्रमागतerated.item[0] = spec->indep_hp_enabled;
	वापस 0;
पूर्ण

अटल व्योम update_aamix_paths(काष्ठा hda_codec *codec, bool करो_mix,
			       पूर्णांक nomix_path_idx, पूर्णांक mix_path_idx,
			       पूर्णांक out_type);

अटल पूर्णांक indep_hp_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	अचिन्हित पूर्णांक select = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक ret = 0;

	mutex_lock(&spec->pcm_mutex);
	अगर (spec->active_streams) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	अगर (spec->indep_hp_enabled != select) अणु
		hda_nid_t *dacp;
		अगर (spec->स्वतःcfg.line_out_type == AUTO_PIN_HP_OUT)
			dacp = &spec->निजी_dac_nids[0];
		अन्यथा
			dacp = &spec->multiout.hp_out_nid[0];

		/* update HP aamix paths in हाल it conflicts with indep HP */
		अगर (spec->have_aamix_ctl) अणु
			अगर (spec->स्वतःcfg.line_out_type == AUTO_PIN_HP_OUT)
				update_aamix_paths(codec, spec->aamix_mode,
						   spec->out_paths[0],
						   spec->aamix_out_paths[0],
						   spec->स्वतःcfg.line_out_type);
			अन्यथा
				update_aamix_paths(codec, spec->aamix_mode,
						   spec->hp_paths[0],
						   spec->aamix_out_paths[1],
						   AUTO_PIN_HP_OUT);
		पूर्ण

		spec->indep_hp_enabled = select;
		अगर (spec->indep_hp_enabled)
			*dacp = 0;
		अन्यथा
			*dacp = spec->alt_dac_nid;

		call_hp_स्वतःmute(codec, शून्य);
		ret = 1;
	पूर्ण
 unlock:
	mutex_unlock(&spec->pcm_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new indep_hp_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Independent HP",
	.info = indep_hp_info,
	.get = indep_hp_get,
	.put = indep_hp_put,
पूर्ण;


अटल पूर्णांक create_indep_hp_ctls(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	hda_nid_t dac;

	अगर (!spec->indep_hp)
		वापस 0;
	अगर (spec->स्वतःcfg.line_out_type == AUTO_PIN_HP_OUT)
		dac = spec->multiout.dac_nids[0];
	अन्यथा
		dac = spec->multiout.hp_out_nid[0];
	अगर (!dac) अणु
		spec->indep_hp = 0;
		वापस 0;
	पूर्ण

	spec->indep_hp_enabled = false;
	spec->alt_dac_nid = dac;
	अगर (!snd_hda_gen_add_kctl(spec, शून्य, &indep_hp_ctl))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/*
 * channel mode क्रमागत control
 */

अटल पूर्णांक ch_mode_info(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक chs;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = spec->multi_ios + 1;
	अगर (uinfo->value.क्रमागतerated.item > spec->multi_ios)
		uinfo->value.क्रमागतerated.item = spec->multi_ios;
	chs = uinfo->value.क्रमागतerated.item * 2 + spec->min_channel_count;
	प्र_लिखो(uinfo->value.क्रमागतerated.name, "%dch", chs);
	वापस 0;
पूर्ण

अटल पूर्णांक ch_mode_get(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	ucontrol->value.क्रमागतerated.item[0] =
		(spec->ext_channel_count - spec->min_channel_count) / 2;
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा nid_path *
get_multiio_path(काष्ठा hda_codec *codec, पूर्णांक idx)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	वापस snd_hda_get_path_from_idx(codec,
		spec->out_paths[spec->स्वतःcfg.line_outs + idx]);
पूर्ण

अटल व्योम update_स्वतःmute_all(काष्ठा hda_codec *codec);

/* Default value to be passed as aamix argument क्रम snd_hda_activate_path();
 * used क्रम output paths
 */
अटल bool aamix_शेष(काष्ठा hda_gen_spec *spec)
अणु
	वापस !spec->have_aamix_ctl || spec->aamix_mode;
पूर्ण

अटल पूर्णांक set_multi_io(काष्ठा hda_codec *codec, पूर्णांक idx, bool output)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	hda_nid_t nid = spec->multi_io[idx].pin;
	काष्ठा nid_path *path;

	path = get_multiio_path(codec, idx);
	अगर (!path)
		वापस -EINVAL;

	अगर (path->active == output)
		वापस 0;

	अगर (output) अणु
		set_pin_target(codec, nid, PIN_OUT, true);
		snd_hda_activate_path(codec, path, true, aamix_शेष(spec));
		set_pin_eapd(codec, nid, true);
	पूर्ण अन्यथा अणु
		set_pin_eapd(codec, nid, false);
		snd_hda_activate_path(codec, path, false, aamix_शेष(spec));
		set_pin_target(codec, nid, spec->multi_io[idx].ctl_in, true);
		path_घातer_करोwn_sync(codec, path);
	पूर्ण

	/* update jack retasking in हाल it modअगरies any of them */
	update_स्वतःmute_all(codec);

	वापस 0;
पूर्ण

अटल पूर्णांक ch_mode_put(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i, ch;

	ch = ucontrol->value.क्रमागतerated.item[0];
	अगर (ch < 0 || ch > spec->multi_ios)
		वापस -EINVAL;
	अगर (ch == (spec->ext_channel_count - spec->min_channel_count) / 2)
		वापस 0;
	spec->ext_channel_count = ch * 2 + spec->min_channel_count;
	क्रम (i = 0; i < spec->multi_ios; i++)
		set_multi_io(codec, i, i < ch);
	spec->multiout.max_channels = max(spec->ext_channel_count,
					  spec->स्थिर_channel_count);
	अगर (spec->need_dac_fix)
		spec->multiout.num_dacs = spec->multiout.max_channels / 2;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new channel_mode_क्रमागत = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Channel Mode",
	.info = ch_mode_info,
	.get = ch_mode_get,
	.put = ch_mode_put,
पूर्ण;

अटल पूर्णांक create_multi_channel_mode(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;

	अगर (spec->multi_ios > 0) अणु
		अगर (!snd_hda_gen_add_kctl(spec, शून्य, &channel_mode_क्रमागत))
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * aamix loopback enable/disable चयन
 */

#घोषणा loopback_mixing_info	indep_hp_info

अटल पूर्णांक loopback_mixing_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	ucontrol->value.क्रमागतerated.item[0] = spec->aamix_mode;
	वापस 0;
पूर्ण

अटल व्योम update_aamix_paths(काष्ठा hda_codec *codec, bool करो_mix,
			       पूर्णांक nomix_path_idx, पूर्णांक mix_path_idx,
			       पूर्णांक out_type)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा nid_path *nomix_path, *mix_path;

	nomix_path = snd_hda_get_path_from_idx(codec, nomix_path_idx);
	mix_path = snd_hda_get_path_from_idx(codec, mix_path_idx);
	अगर (!nomix_path || !mix_path)
		वापस;

	/* अगर HP aamix path is driven from a dअगरferent DAC and the
	 * independent HP mode is ON, can't turn on aamix path
	 */
	अगर (out_type == AUTO_PIN_HP_OUT && spec->indep_hp_enabled &&
	    mix_path->path[0] != spec->alt_dac_nid)
		करो_mix = false;

	अगर (करो_mix) अणु
		snd_hda_activate_path(codec, nomix_path, false, true);
		snd_hda_activate_path(codec, mix_path, true, true);
		path_घातer_करोwn_sync(codec, nomix_path);
	पूर्ण अन्यथा अणु
		snd_hda_activate_path(codec, mix_path, false, false);
		snd_hda_activate_path(codec, nomix_path, true, false);
		path_घातer_करोwn_sync(codec, mix_path);
	पूर्ण
पूर्ण

/* re-initialize the output paths; only called from loopback_mixing_put() */
अटल व्योम update_output_paths(काष्ठा hda_codec *codec, पूर्णांक num_outs,
				स्थिर पूर्णांक *paths)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा nid_path *path;
	पूर्णांक i;

	क्रम (i = 0; i < num_outs; i++) अणु
		path = snd_hda_get_path_from_idx(codec, paths[i]);
		अगर (path)
			snd_hda_activate_path(codec, path, path->active,
					      spec->aamix_mode);
	पूर्ण
पूर्ण

अटल पूर्णांक loopback_mixing_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	स्थिर काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	अचिन्हित पूर्णांक val = ucontrol->value.क्रमागतerated.item[0];

	अगर (val == spec->aamix_mode)
		वापस 0;
	spec->aamix_mode = val;
	अगर (has_aamix_out_paths(spec)) अणु
		update_aamix_paths(codec, val, spec->out_paths[0],
				   spec->aamix_out_paths[0],
				   cfg->line_out_type);
		update_aamix_paths(codec, val, spec->hp_paths[0],
				   spec->aamix_out_paths[1],
				   AUTO_PIN_HP_OUT);
		update_aamix_paths(codec, val, spec->speaker_paths[0],
				   spec->aamix_out_paths[2],
				   AUTO_PIN_SPEAKER_OUT);
	पूर्ण अन्यथा अणु
		update_output_paths(codec, cfg->line_outs, spec->out_paths);
		अगर (cfg->line_out_type != AUTO_PIN_HP_OUT)
			update_output_paths(codec, cfg->hp_outs, spec->hp_paths);
		अगर (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT)
			update_output_paths(codec, cfg->speaker_outs,
					    spec->speaker_paths);
	पूर्ण
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new loopback_mixing_क्रमागत = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Loopback Mixing",
	.info = loopback_mixing_info,
	.get = loopback_mixing_get,
	.put = loopback_mixing_put,
पूर्ण;

अटल पूर्णांक create_loopback_mixing_ctl(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;

	अगर (!spec->mixer_nid)
		वापस 0;
	अगर (!snd_hda_gen_add_kctl(spec, शून्य, &loopback_mixing_क्रमागत))
		वापस -ENOMEM;
	spec->have_aamix_ctl = 1;
	वापस 0;
पूर्ण

/*
 * shared headphone/mic handling
 */

अटल व्योम call_update_outमाला_दो(काष्ठा hda_codec *codec);

/* क्रम shared I/O, change the pin-control accordingly */
अटल व्योम update_hp_mic(काष्ठा hda_codec *codec, पूर्णांक adc_mux, bool क्रमce)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	bool as_mic;
	अचिन्हित पूर्णांक val;
	hda_nid_t pin;

	pin = spec->hp_mic_pin;
	as_mic = spec->cur_mux[adc_mux] == spec->hp_mic_mux_idx;

	अगर (!क्रमce) अणु
		val = snd_hda_codec_get_pin_target(codec, pin);
		अगर (as_mic) अणु
			अगर (val & PIN_IN)
				वापस;
		पूर्ण अन्यथा अणु
			अगर (val & PIN_OUT)
				वापस;
		पूर्ण
	पूर्ण

	val = snd_hda_get_शेष_vref(codec, pin);
	/* अगर the HP pin करोesn't support VREF and the codec driver gives an
	 * alternative pin, set up the VREF on that pin instead
	 */
	अगर (val == AC_PINCTL_VREF_HIZ && spec->shared_mic_vref_pin) अणु
		स्थिर hda_nid_t vref_pin = spec->shared_mic_vref_pin;
		अचिन्हित पूर्णांक vref_val = snd_hda_get_शेष_vref(codec, vref_pin);
		अगर (vref_val != AC_PINCTL_VREF_HIZ)
			snd_hda_set_pin_ctl_cache(codec, vref_pin,
						  PIN_IN | (as_mic ? vref_val : 0));
	पूर्ण

	अगर (!spec->hp_mic_jack_modes) अणु
		अगर (as_mic)
			val |= PIN_IN;
		अन्यथा
			val = PIN_HP;
		set_pin_target(codec, pin, val, true);
		call_hp_स्वतःmute(codec, शून्य);
	पूर्ण
पूर्ण

/* create a shared input with the headphone out */
अटल पूर्णांक create_hp_mic(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	अचिन्हित पूर्णांक defcfg;
	hda_nid_t nid;

	अगर (!spec->hp_mic) अणु
		अगर (spec->suppress_hp_mic_detect)
			वापस 0;
		/* स्वतःmatic detection: only अगर no input or a single पूर्णांकernal
		 * input pin is found, try to detect the shared hp/mic
		 */
		अगर (cfg->num_inमाला_दो > 1)
			वापस 0;
		अन्यथा अगर (cfg->num_inमाला_दो == 1) अणु
			defcfg = snd_hda_codec_get_pincfg(codec, cfg->inमाला_दो[0].pin);
			अगर (snd_hda_get_input_pin_attr(defcfg) != INPUT_PIN_ATTR_INT)
				वापस 0;
		पूर्ण
	पूर्ण

	spec->hp_mic = 0; /* clear once */
	अगर (cfg->num_inमाला_दो >= AUTO_CFG_MAX_INS)
		वापस 0;

	nid = 0;
	अगर (cfg->line_out_type == AUTO_PIN_HP_OUT && cfg->line_outs > 0)
		nid = cfg->line_out_pins[0];
	अन्यथा अगर (cfg->hp_outs > 0)
		nid = cfg->hp_pins[0];
	अगर (!nid)
		वापस 0;

	अगर (!(snd_hda_query_pin_caps(codec, nid) & AC_PINCAP_IN))
		वापस 0; /* no input */

	cfg->inमाला_दो[cfg->num_inमाला_दो].pin = nid;
	cfg->inमाला_दो[cfg->num_inमाला_दो].type = AUTO_PIN_MIC;
	cfg->inमाला_दो[cfg->num_inमाला_दो].is_headphone_mic = 1;
	cfg->num_inमाला_दो++;
	spec->hp_mic = 1;
	spec->hp_mic_pin = nid;
	/* we can't handle स्वतः-mic together with HP-mic */
	spec->suppress_स्वतः_mic = 1;
	codec_dbg(codec, "Enable shared I/O jack on NID 0x%x\n", nid);
	वापस 0;
पूर्ण

/*
 * output jack mode
 */

अटल पूर्णांक create_hp_mic_jack_mode(काष्ठा hda_codec *codec, hda_nid_t pin);

अटल स्थिर अक्षर * स्थिर out_jack_texts[] = अणु
	"Line Out", "Headphone Out",
पूर्ण;

अटल पूर्णांक out_jack_mode_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	वापस snd_hda_क्रमागत_helper_info(kcontrol, uinfo, 2, out_jack_texts);
पूर्ण

अटल पूर्णांक out_jack_mode_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->निजी_value;
	अगर (snd_hda_codec_get_pin_target(codec, nid) == PIN_HP)
		ucontrol->value.क्रमागतerated.item[0] = 1;
	अन्यथा
		ucontrol->value.क्रमागतerated.item[0] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक out_jack_mode_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->निजी_value;
	अचिन्हित पूर्णांक val;

	val = ucontrol->value.क्रमागतerated.item[0] ? PIN_HP : PIN_OUT;
	अगर (snd_hda_codec_get_pin_target(codec, nid) == val)
		वापस 0;
	snd_hda_set_pin_ctl_cache(codec, nid, val);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new out_jack_mode_क्रमागत = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.info = out_jack_mode_info,
	.get = out_jack_mode_get,
	.put = out_jack_mode_put,
पूर्ण;

अटल bool find_kctl_name(काष्ठा hda_codec *codec, स्थिर अक्षर *name, पूर्णांक idx)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	स्थिर काष्ठा snd_kcontrol_new *kctl;
	पूर्णांक i;

	snd_array_क्रम_each(&spec->kctls, i, kctl) अणु
		अगर (!म_भेद(kctl->name, name) && kctl->index == idx)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम get_jack_mode_name(काष्ठा hda_codec *codec, hda_nid_t pin,
			       अक्षर *name, माप_प्रकार name_len)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक idx = 0;

	snd_hda_get_pin_label(codec, pin, &spec->स्वतःcfg, name, name_len, &idx);
	strlcat(name, " Jack Mode", name_len);

	क्रम (; find_kctl_name(codec, name, idx); idx++)
		;
पूर्ण

अटल पूर्णांक get_out_jack_num_items(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	अगर (spec->add_jack_modes) अणु
		अचिन्हित पूर्णांक pincap = snd_hda_query_pin_caps(codec, pin);
		अगर ((pincap & AC_PINCAP_OUT) && (pincap & AC_PINCAP_HP_DRV))
			वापस 2;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक create_out_jack_modes(काष्ठा hda_codec *codec, पूर्णांक num_pins,
				 hda_nid_t *pins)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i;

	क्रम (i = 0; i < num_pins; i++) अणु
		hda_nid_t pin = pins[i];
		अगर (pin == spec->hp_mic_pin)
			जारी;
		अगर (get_out_jack_num_items(codec, pin) > 1) अणु
			काष्ठा snd_kcontrol_new *knew;
			अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
			get_jack_mode_name(codec, pin, name, माप(name));
			knew = snd_hda_gen_add_kctl(spec, name,
						    &out_jack_mode_क्रमागत);
			अगर (!knew)
				वापस -ENOMEM;
			knew->निजी_value = pin;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * input jack mode
 */

/* from AC_PINCTL_VREF_HIZ to AC_PINCTL_VREF_100 */
#घोषणा NUM_VREFS	6

अटल स्थिर अक्षर * स्थिर vref_texts[NUM_VREFS] = अणु
	"Line In", "Mic 50pc Bias", "Mic 0V Bias",
	"", "Mic 80pc Bias", "Mic 100pc Bias"
पूर्ण;

अटल अचिन्हित पूर्णांक get_vref_caps(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	अचिन्हित पूर्णांक pincap;

	pincap = snd_hda_query_pin_caps(codec, pin);
	pincap = (pincap & AC_PINCAP_VREF) >> AC_PINCAP_VREF_SHIFT;
	/* filter out unusual vrefs */
	pincap &= ~(AC_PINCAP_VREF_GRD | AC_PINCAP_VREF_100);
	वापस pincap;
पूर्ण

/* convert from the क्रमागत item index to the vref ctl index (0=HIZ, 1=50%...) */
अटल पूर्णांक get_vref_idx(अचिन्हित पूर्णांक vref_caps, अचिन्हित पूर्णांक item_idx)
अणु
	अचिन्हित पूर्णांक i, n = 0;

	क्रम (i = 0; i < NUM_VREFS; i++) अणु
		अगर (vref_caps & (1 << i)) अणु
			अगर (n == item_idx)
				वापस i;
			n++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* convert back from the vref ctl index to the क्रमागत item index */
अटल पूर्णांक cvt_from_vref_idx(अचिन्हित पूर्णांक vref_caps, अचिन्हित पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक i, n = 0;

	क्रम (i = 0; i < NUM_VREFS; i++) अणु
		अगर (i == idx)
			वापस n;
		अगर (vref_caps & (1 << i))
			n++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक in_jack_mode_info(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->निजी_value;
	अचिन्हित पूर्णांक vref_caps = get_vref_caps(codec, nid);

	snd_hda_क्रमागत_helper_info(kcontrol, uinfo, hweight32(vref_caps),
				 vref_texts);
	/* set the right text */
	म_नकल(uinfo->value.क्रमागतerated.name,
	       vref_texts[get_vref_idx(vref_caps, uinfo->value.क्रमागतerated.item)]);
	वापस 0;
पूर्ण

अटल पूर्णांक in_jack_mode_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->निजी_value;
	अचिन्हित पूर्णांक vref_caps = get_vref_caps(codec, nid);
	अचिन्हित पूर्णांक idx;

	idx = snd_hda_codec_get_pin_target(codec, nid) & AC_PINCTL_VREFEN;
	ucontrol->value.क्रमागतerated.item[0] = cvt_from_vref_idx(vref_caps, idx);
	वापस 0;
पूर्ण

अटल पूर्णांक in_jack_mode_put(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->निजी_value;
	अचिन्हित पूर्णांक vref_caps = get_vref_caps(codec, nid);
	अचिन्हित पूर्णांक val, idx;

	val = snd_hda_codec_get_pin_target(codec, nid);
	idx = cvt_from_vref_idx(vref_caps, val & AC_PINCTL_VREFEN);
	अगर (idx == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	val &= ~AC_PINCTL_VREFEN;
	val |= get_vref_idx(vref_caps, ucontrol->value.क्रमागतerated.item[0]);
	snd_hda_set_pin_ctl_cache(codec, nid, val);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new in_jack_mode_क्रमागत = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.info = in_jack_mode_info,
	.get = in_jack_mode_get,
	.put = in_jack_mode_put,
पूर्ण;

अटल पूर्णांक get_in_jack_num_items(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक nitems = 0;
	अगर (spec->add_jack_modes)
		nitems = hweight32(get_vref_caps(codec, pin));
	वापस nitems ? nitems : 1;
पूर्ण

अटल पूर्णांक create_in_jack_mode(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा snd_kcontrol_new *knew;
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	अचिन्हित पूर्णांक defcfg;

	अगर (pin == spec->hp_mic_pin)
		वापस 0; /* alपढ़ोy करोne in create_out_jack_mode() */

	/* no jack mode क्रम fixed pins */
	defcfg = snd_hda_codec_get_pincfg(codec, pin);
	अगर (snd_hda_get_input_pin_attr(defcfg) == INPUT_PIN_ATTR_INT)
		वापस 0;

	/* no multiple vref caps? */
	अगर (get_in_jack_num_items(codec, pin) <= 1)
		वापस 0;

	get_jack_mode_name(codec, pin, name, माप(name));
	knew = snd_hda_gen_add_kctl(spec, name, &in_jack_mode_क्रमागत);
	अगर (!knew)
		वापस -ENOMEM;
	knew->निजी_value = pin;
	वापस 0;
पूर्ण

/*
 * HP/mic shared jack mode
 */
अटल पूर्णांक hp_mic_jack_mode_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->निजी_value;
	पूर्णांक out_jacks = get_out_jack_num_items(codec, nid);
	पूर्णांक in_jacks = get_in_jack_num_items(codec, nid);
	स्थिर अक्षर *text = शून्य;
	पूर्णांक idx;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = out_jacks + in_jacks;
	अगर (uinfo->value.क्रमागतerated.item >= uinfo->value.क्रमागतerated.items)
		uinfo->value.क्रमागतerated.item = uinfo->value.क्रमागतerated.items - 1;
	idx = uinfo->value.क्रमागतerated.item;
	अगर (idx < out_jacks) अणु
		अगर (out_jacks > 1)
			text = out_jack_texts[idx];
		अन्यथा
			text = "Headphone Out";
	पूर्ण अन्यथा अणु
		idx -= out_jacks;
		अगर (in_jacks > 1) अणु
			अचिन्हित पूर्णांक vref_caps = get_vref_caps(codec, nid);
			text = vref_texts[get_vref_idx(vref_caps, idx)];
		पूर्ण अन्यथा
			text = "Mic In";
	पूर्ण

	म_नकल(uinfo->value.क्रमागतerated.name, text);
	वापस 0;
पूर्ण

अटल पूर्णांक get_cur_hp_mic_jack_mode(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	पूर्णांक out_jacks = get_out_jack_num_items(codec, nid);
	पूर्णांक in_jacks = get_in_jack_num_items(codec, nid);
	अचिन्हित पूर्णांक val = snd_hda_codec_get_pin_target(codec, nid);
	पूर्णांक idx = 0;

	अगर (val & PIN_OUT) अणु
		अगर (out_jacks > 1 && val == PIN_HP)
			idx = 1;
	पूर्ण अन्यथा अगर (val & PIN_IN) अणु
		idx = out_jacks;
		अगर (in_jacks > 1) अणु
			अचिन्हित पूर्णांक vref_caps = get_vref_caps(codec, nid);
			val &= AC_PINCTL_VREFEN;
			idx += cvt_from_vref_idx(vref_caps, val);
		पूर्ण
	पूर्ण
	वापस idx;
पूर्ण

अटल पूर्णांक hp_mic_jack_mode_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->निजी_value;
	ucontrol->value.क्रमागतerated.item[0] =
		get_cur_hp_mic_jack_mode(codec, nid);
	वापस 0;
पूर्ण

अटल पूर्णांक hp_mic_jack_mode_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->निजी_value;
	पूर्णांक out_jacks = get_out_jack_num_items(codec, nid);
	पूर्णांक in_jacks = get_in_jack_num_items(codec, nid);
	अचिन्हित पूर्णांक val, oldval, idx;

	oldval = get_cur_hp_mic_jack_mode(codec, nid);
	idx = ucontrol->value.क्रमागतerated.item[0];
	अगर (oldval == idx)
		वापस 0;

	अगर (idx < out_jacks) अणु
		अगर (out_jacks > 1)
			val = idx ? PIN_HP : PIN_OUT;
		अन्यथा
			val = PIN_HP;
	पूर्ण अन्यथा अणु
		idx -= out_jacks;
		अगर (in_jacks > 1) अणु
			अचिन्हित पूर्णांक vref_caps = get_vref_caps(codec, nid);
			val = snd_hda_codec_get_pin_target(codec, nid);
			val &= ~(AC_PINCTL_VREFEN | PIN_HP);
			val |= get_vref_idx(vref_caps, idx) | PIN_IN;
		पूर्ण अन्यथा
			val = snd_hda_get_शेष_vref(codec, nid) | PIN_IN;
	पूर्ण
	snd_hda_set_pin_ctl_cache(codec, nid, val);
	call_hp_स्वतःmute(codec, शून्य);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new hp_mic_jack_mode_क्रमागत = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.info = hp_mic_jack_mode_info,
	.get = hp_mic_jack_mode_get,
	.put = hp_mic_jack_mode_put,
पूर्ण;

अटल पूर्णांक create_hp_mic_jack_mode(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा snd_kcontrol_new *knew;

	knew = snd_hda_gen_add_kctl(spec, "Headphone Mic Jack Mode",
				    &hp_mic_jack_mode_क्रमागत);
	अगर (!knew)
		वापस -ENOMEM;
	knew->निजी_value = pin;
	spec->hp_mic_jack_modes = 1;
	वापस 0;
पूर्ण

/*
 * Parse input paths
 */

/* add the घातersave loopback-list entry */
अटल पूर्णांक add_loopback_list(काष्ठा hda_gen_spec *spec, hda_nid_t mix, पूर्णांक idx)
अणु
	काष्ठा hda_amp_list *list;

	list = snd_array_new(&spec->loopback_list);
	अगर (!list)
		वापस -ENOMEM;
	list->nid = mix;
	list->dir = HDA_INPUT;
	list->idx = idx;
	spec->loopback.amplist = spec->loopback_list.list;
	वापस 0;
पूर्ण

/* वापस true अगर either a volume or a mute amp is found क्रम the given
 * aamix path; the amp has to be either in the mixer node or its direct leaf
 */
अटल bool look_क्रम_mix_leaf_ctls(काष्ठा hda_codec *codec, hda_nid_t mix_nid,
				   hda_nid_t pin, अचिन्हित पूर्णांक *mix_val,
				   अचिन्हित पूर्णांक *mute_val)
अणु
	पूर्णांक idx, num_conns;
	स्थिर hda_nid_t *list;
	hda_nid_t nid;

	idx = snd_hda_get_conn_index(codec, mix_nid, pin, true);
	अगर (idx < 0)
		वापस false;

	*mix_val = *mute_val = 0;
	अगर (nid_has_volume(codec, mix_nid, HDA_INPUT))
		*mix_val = HDA_COMPOSE_AMP_VAL(mix_nid, 3, idx, HDA_INPUT);
	अगर (nid_has_mute(codec, mix_nid, HDA_INPUT))
		*mute_val = HDA_COMPOSE_AMP_VAL(mix_nid, 3, idx, HDA_INPUT);
	अगर (*mix_val && *mute_val)
		वापस true;

	/* check leaf node */
	num_conns = snd_hda_get_conn_list(codec, mix_nid, &list);
	अगर (num_conns < idx)
		वापस false;
	nid = list[idx];
	अगर (!*mix_val && nid_has_volume(codec, nid, HDA_OUTPUT) &&
	    !is_ctl_associated(codec, nid, HDA_OUTPUT, 0, NID_PATH_VOL_CTL))
		*mix_val = HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_OUTPUT);
	अगर (!*mute_val && nid_has_mute(codec, nid, HDA_OUTPUT) &&
	    !is_ctl_associated(codec, nid, HDA_OUTPUT, 0, NID_PATH_MUTE_CTL))
		*mute_val = HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_OUTPUT);

	वापस *mix_val || *mute_val;
पूर्ण

/* create input playback/capture controls क्रम the given pin */
अटल पूर्णांक new_analog_input(काष्ठा hda_codec *codec, पूर्णांक input_idx,
			    hda_nid_t pin, स्थिर अक्षर *ctlname, पूर्णांक ctlidx,
			    hda_nid_t mix_nid)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा nid_path *path;
	अचिन्हित पूर्णांक mix_val, mute_val;
	पूर्णांक err, idx;

	अगर (!look_क्रम_mix_leaf_ctls(codec, mix_nid, pin, &mix_val, &mute_val))
		वापस 0;

	path = snd_hda_add_new_path(codec, pin, mix_nid, 0);
	अगर (!path)
		वापस -EINVAL;
	prपूर्णांक_nid_path(codec, "loopback", path);
	spec->loopback_paths[input_idx] = snd_hda_get_path_idx(codec, path);

	idx = path->idx[path->depth - 1];
	अगर (mix_val) अणु
		err = __add_pb_vol_ctrl(spec, HDA_CTL_WIDGET_VOL, ctlname, ctlidx, mix_val);
		अगर (err < 0)
			वापस err;
		path->ctls[NID_PATH_VOL_CTL] = mix_val;
	पूर्ण

	अगर (mute_val) अणु
		err = __add_pb_sw_ctrl(spec, HDA_CTL_WIDGET_MUTE, ctlname, ctlidx, mute_val);
		अगर (err < 0)
			वापस err;
		path->ctls[NID_PATH_MUTE_CTL] = mute_val;
	पूर्ण

	path->active = true;
	path->stream_enabled = true; /* no DAC/ADC involved */
	err = add_loopback_list(spec, mix_nid, idx);
	अगर (err < 0)
		वापस err;

	अगर (spec->mixer_nid != spec->mixer_merge_nid &&
	    !spec->loopback_merge_path) अणु
		path = snd_hda_add_new_path(codec, spec->mixer_nid,
					    spec->mixer_merge_nid, 0);
		अगर (path) अणु
			prपूर्णांक_nid_path(codec, "loopback-merge", path);
			path->active = true;
			path->pin_fixed = true; /* अटल route */
			path->stream_enabled = true; /* no DAC/ADC involved */
			spec->loopback_merge_path =
				snd_hda_get_path_idx(codec, path);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक is_input_pin(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक pincap = snd_hda_query_pin_caps(codec, nid);
	वापस (pincap & AC_PINCAP_IN) != 0;
पूर्ण

/* Parse the codec tree and retrieve ADCs */
अटल पूर्णांक fill_adc_nids(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	hda_nid_t nid;
	hda_nid_t *adc_nids = spec->adc_nids;
	पूर्णांक max_nums = ARRAY_SIZE(spec->adc_nids);
	पूर्णांक nums = 0;

	क्रम_each_hda_codec_node(nid, codec) अणु
		अचिन्हित पूर्णांक caps = get_wcaps(codec, nid);
		पूर्णांक type = get_wcaps_type(caps);

		अगर (type != AC_WID_AUD_IN || (caps & AC_WCAP_DIGITAL))
			जारी;
		adc_nids[nums] = nid;
		अगर (++nums >= max_nums)
			अवरोध;
	पूर्ण
	spec->num_adc_nids = nums;

	/* copy the detected ADCs to all_adcs[] */
	spec->num_all_adcs = nums;
	स_नकल(spec->all_adcs, spec->adc_nids, nums * माप(hda_nid_t));

	वापस nums;
पूर्ण

/* filter out invalid adc_nids that करोn't give all active input pins;
 * अगर needed, check whether dynamic ADC-चयनing is available
 */
अटल पूर्णांक check_dyn_adc_चयन(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा hda_input_mux *imux = &spec->input_mux;
	अचिन्हित पूर्णांक ok_bits;
	पूर्णांक i, n, nums;

	nums = 0;
	ok_bits = 0;
	क्रम (n = 0; n < spec->num_adc_nids; n++) अणु
		क्रम (i = 0; i < imux->num_items; i++) अणु
			अगर (!spec->input_paths[i][n])
				अवरोध;
		पूर्ण
		अगर (i >= imux->num_items) अणु
			ok_bits |= (1 << n);
			nums++;
		पूर्ण
	पूर्ण

	अगर (!ok_bits) अणु
		/* check whether ADC-चयन is possible */
		क्रम (i = 0; i < imux->num_items; i++) अणु
			क्रम (n = 0; n < spec->num_adc_nids; n++) अणु
				अगर (spec->input_paths[i][n]) अणु
					spec->dyn_adc_idx[i] = n;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		codec_dbg(codec, "enabling ADC switching\n");
		spec->dyn_adc_चयन = 1;
	पूर्ण अन्यथा अगर (nums != spec->num_adc_nids) अणु
		/* shrink the invalid adcs and input paths */
		nums = 0;
		क्रम (n = 0; n < spec->num_adc_nids; n++) अणु
			अगर (!(ok_bits & (1 << n)))
				जारी;
			अगर (n != nums) अणु
				spec->adc_nids[nums] = spec->adc_nids[n];
				क्रम (i = 0; i < imux->num_items; i++) अणु
					invalidate_nid_path(codec,
						spec->input_paths[i][nums]);
					spec->input_paths[i][nums] =
						spec->input_paths[i][n];
					spec->input_paths[i][n] = 0;
				पूर्ण
			पूर्ण
			nums++;
		पूर्ण
		spec->num_adc_nids = nums;
	पूर्ण

	अगर (imux->num_items == 1 ||
	    (imux->num_items == 2 && spec->hp_mic)) अणु
		codec_dbg(codec, "reducing to a single ADC\n");
		spec->num_adc_nids = 1; /* reduce to a single ADC */
	पूर्ण

	/* single index क्रम inभागidual volumes ctls */
	अगर (!spec->dyn_adc_चयन && spec->multi_cap_vol)
		spec->num_adc_nids = 1;

	वापस 0;
पूर्ण

/* parse capture source paths from the given pin and create imux items */
अटल पूर्णांक parse_capture_source(काष्ठा hda_codec *codec, hda_nid_t pin,
				पूर्णांक cfg_idx, पूर्णांक num_adcs,
				स्थिर अक्षर *label, पूर्णांक anchor)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा hda_input_mux *imux = &spec->input_mux;
	पूर्णांक imux_idx = imux->num_items;
	bool imux_added = false;
	पूर्णांक c;

	क्रम (c = 0; c < num_adcs; c++) अणु
		काष्ठा nid_path *path;
		hda_nid_t adc = spec->adc_nids[c];

		अगर (!is_reachable_path(codec, pin, adc))
			जारी;
		path = snd_hda_add_new_path(codec, pin, adc, anchor);
		अगर (!path)
			जारी;
		prपूर्णांक_nid_path(codec, "input", path);
		spec->input_paths[imux_idx][c] =
			snd_hda_get_path_idx(codec, path);

		अगर (!imux_added) अणु
			अगर (spec->hp_mic_pin == pin)
				spec->hp_mic_mux_idx = imux->num_items;
			spec->imux_pins[imux->num_items] = pin;
			snd_hda_add_imux_item(codec, imux, label, cfg_idx, शून्य);
			imux_added = true;
			अगर (spec->dyn_adc_चयन)
				spec->dyn_adc_idx[imux_idx] = c;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * create playback/capture controls क्रम input pins
 */

/* fill the label क्रम each input at first */
अटल पूर्णांक fill_input_pin_labels(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	स्थिर काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	पूर्णांक i;

	क्रम (i = 0; i < cfg->num_inमाला_दो; i++) अणु
		hda_nid_t pin = cfg->inमाला_दो[i].pin;
		स्थिर अक्षर *label;
		पूर्णांक j, idx;

		अगर (!is_input_pin(codec, pin))
			जारी;

		label = hda_get_स्वतःcfg_input_label(codec, cfg, i);
		idx = 0;
		क्रम (j = i - 1; j >= 0; j--) अणु
			अगर (spec->input_labels[j] &&
			    !म_भेद(spec->input_labels[j], label)) अणु
				idx = spec->input_label_idxs[j] + 1;
				अवरोध;
			पूर्ण
		पूर्ण

		spec->input_labels[i] = label;
		spec->input_label_idxs[i] = idx;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा CFG_IDX_MIX	99	/* a dummy cfg->input idx क्रम stereo mix */

अटल पूर्णांक create_input_ctls(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	स्थिर काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	hda_nid_t mixer = spec->mixer_nid;
	पूर्णांक num_adcs;
	पूर्णांक i, err;
	अचिन्हित पूर्णांक val;

	num_adcs = fill_adc_nids(codec);
	अगर (num_adcs < 0)
		वापस 0;

	err = fill_input_pin_labels(codec);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < cfg->num_inमाला_दो; i++) अणु
		hda_nid_t pin;

		pin = cfg->inमाला_दो[i].pin;
		अगर (!is_input_pin(codec, pin))
			जारी;

		val = PIN_IN;
		अगर (cfg->inमाला_दो[i].type == AUTO_PIN_MIC)
			val |= snd_hda_get_शेष_vref(codec, pin);
		अगर (pin != spec->hp_mic_pin &&
		    !snd_hda_codec_get_pin_target(codec, pin))
			set_pin_target(codec, pin, val, false);

		अगर (mixer) अणु
			अगर (is_reachable_path(codec, pin, mixer)) अणु
				err = new_analog_input(codec, i, pin,
						       spec->input_labels[i],
						       spec->input_label_idxs[i],
						       mixer);
				अगर (err < 0)
					वापस err;
			पूर्ण
		पूर्ण

		err = parse_capture_source(codec, pin, i, num_adcs,
					   spec->input_labels[i], -mixer);
		अगर (err < 0)
			वापस err;

		अगर (spec->add_jack_modes) अणु
			err = create_in_jack_mode(codec, pin);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	/* add stereo mix when explicitly enabled via hपूर्णांक */
	अगर (mixer && spec->add_stereo_mix_input == HDA_HINT_STEREO_MIX_ENABLE) अणु
		err = parse_capture_source(codec, mixer, CFG_IDX_MIX, num_adcs,
					   "Stereo Mix", 0);
		अगर (err < 0)
			वापस err;
		अन्यथा
			spec->suppress_स्वतः_mic = 1;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * input source mux
 */

/* get the input path specअगरied by the given adc and imux indices */
अटल काष्ठा nid_path *get_input_path(काष्ठा hda_codec *codec, पूर्णांक adc_idx, पूर्णांक imux_idx)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	अगर (imux_idx < 0 || imux_idx >= HDA_MAX_NUM_INPUTS) अणु
		snd_BUG();
		वापस शून्य;
	पूर्ण
	अगर (spec->dyn_adc_चयन)
		adc_idx = spec->dyn_adc_idx[imux_idx];
	अगर (adc_idx < 0 || adc_idx >= AUTO_CFG_MAX_INS) अणु
		snd_BUG();
		वापस शून्य;
	पूर्ण
	वापस snd_hda_get_path_from_idx(codec, spec->input_paths[imux_idx][adc_idx]);
पूर्ण

अटल पूर्णांक mux_select(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक adc_idx,
		      अचिन्हित पूर्णांक idx);

अटल पूर्णांक mux_क्रमागत_info(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	वापस snd_hda_input_mux_info(&spec->input_mux, uinfo);
पूर्ण

अटल पूर्णांक mux_क्रमागत_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	/* the ctls are created at once with multiple counts */
	अचिन्हित पूर्णांक adc_idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);

	ucontrol->value.क्रमागतerated.item[0] = spec->cur_mux[adc_idx];
	वापस 0;
पूर्ण

अटल पूर्णांक mux_क्रमागत_put(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक adc_idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	वापस mux_select(codec, adc_idx,
			  ucontrol->value.क्रमागतerated.item[0]);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new cap_src_temp = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Input Source",
	.info = mux_क्रमागत_info,
	.get = mux_क्रमागत_get,
	.put = mux_क्रमागत_put,
पूर्ण;

/*
 * capture volume and capture चयन ctls
 */

प्रकार पूर्णांक (*put_call_t)(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol);

/* call the given amp update function क्रम all amps in the imux list at once */
अटल पूर्णांक cap_put_caller(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol,
			  put_call_t func, पूर्णांक type)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	स्थिर काष्ठा hda_input_mux *imux;
	काष्ठा nid_path *path;
	पूर्णांक i, adc_idx, err = 0;

	imux = &spec->input_mux;
	adc_idx = kcontrol->id.index;
	mutex_lock(&codec->control_mutex);
	क्रम (i = 0; i < imux->num_items; i++) अणु
		path = get_input_path(codec, adc_idx, i);
		अगर (!path || !path->ctls[type])
			जारी;
		kcontrol->निजी_value = path->ctls[type];
		err = func(kcontrol, ucontrol);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	mutex_unlock(&codec->control_mutex);
	अगर (err >= 0 && spec->cap_sync_hook)
		spec->cap_sync_hook(codec, kcontrol, ucontrol);
	वापस err;
पूर्ण

/* capture volume ctl callbacks */
#घोषणा cap_vol_info		snd_hda_mixer_amp_volume_info
#घोषणा cap_vol_get		snd_hda_mixer_amp_volume_get
#घोषणा cap_vol_tlv		snd_hda_mixer_amp_tlv

अटल पूर्णांक cap_vol_put(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	वापस cap_put_caller(kcontrol, ucontrol,
			      snd_hda_mixer_amp_volume_put,
			      NID_PATH_VOL_CTL);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new cap_vol_temp = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Capture Volume",
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_READ |
		   SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK),
	.info = cap_vol_info,
	.get = cap_vol_get,
	.put = cap_vol_put,
	.tlv = अणु .c = cap_vol_tlv पूर्ण,
पूर्ण;

/* capture चयन ctl callbacks */
#घोषणा cap_sw_info		snd_ctl_boolean_stereo_info
#घोषणा cap_sw_get		snd_hda_mixer_amp_चयन_get

अटल पूर्णांक cap_sw_put(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	वापस cap_put_caller(kcontrol, ucontrol,
			      snd_hda_mixer_amp_चयन_put,
			      NID_PATH_MUTE_CTL);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new cap_sw_temp = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Capture Switch",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = cap_sw_info,
	.get = cap_sw_get,
	.put = cap_sw_put,
पूर्ण;

अटल पूर्णांक parse_capvol_in_path(काष्ठा hda_codec *codec, काष्ठा nid_path *path)
अणु
	hda_nid_t nid;
	पूर्णांक i, depth;

	path->ctls[NID_PATH_VOL_CTL] = path->ctls[NID_PATH_MUTE_CTL] = 0;
	क्रम (depth = 0; depth < 3; depth++) अणु
		अगर (depth >= path->depth)
			वापस -EINVAL;
		i = path->depth - depth - 1;
		nid = path->path[i];
		अगर (!path->ctls[NID_PATH_VOL_CTL]) अणु
			अगर (nid_has_volume(codec, nid, HDA_OUTPUT))
				path->ctls[NID_PATH_VOL_CTL] =
					HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_OUTPUT);
			अन्यथा अगर (nid_has_volume(codec, nid, HDA_INPUT)) अणु
				पूर्णांक idx = path->idx[i];
				अगर (!depth && codec->single_adc_amp)
					idx = 0;
				path->ctls[NID_PATH_VOL_CTL] =
					HDA_COMPOSE_AMP_VAL(nid, 3, idx, HDA_INPUT);
			पूर्ण
		पूर्ण
		अगर (!path->ctls[NID_PATH_MUTE_CTL]) अणु
			अगर (nid_has_mute(codec, nid, HDA_OUTPUT))
				path->ctls[NID_PATH_MUTE_CTL] =
					HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_OUTPUT);
			अन्यथा अगर (nid_has_mute(codec, nid, HDA_INPUT)) अणु
				पूर्णांक idx = path->idx[i];
				अगर (!depth && codec->single_adc_amp)
					idx = 0;
				path->ctls[NID_PATH_MUTE_CTL] =
					HDA_COMPOSE_AMP_VAL(nid, 3, idx, HDA_INPUT);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल bool is_inv_dmic_pin(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	अगर (!spec->inv_dmic_split)
		वापस false;
	क्रम (i = 0; i < cfg->num_inमाला_दो; i++) अणु
		अगर (cfg->inमाला_दो[i].pin != nid)
			जारी;
		अगर (cfg->inमाला_दो[i].type != AUTO_PIN_MIC)
			वापस false;
		val = snd_hda_codec_get_pincfg(codec, nid);
		वापस snd_hda_get_input_pin_attr(val) == INPUT_PIN_ATTR_INT;
	पूर्ण
	वापस false;
पूर्ण

/* capture चयन put callback क्रम a single control with hook call */
अटल पूर्णांक cap_single_sw_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक ret;

	ret = snd_hda_mixer_amp_चयन_put(kcontrol, ucontrol);
	अगर (ret < 0)
		वापस ret;

	अगर (spec->cap_sync_hook)
		spec->cap_sync_hook(codec, kcontrol, ucontrol);

	वापस ret;
पूर्ण

अटल पूर्णांक add_single_cap_ctl(काष्ठा hda_codec *codec, स्थिर अक्षर *label,
			      पूर्णांक idx, bool is_चयन, अचिन्हित पूर्णांक ctl,
			      bool inv_dmic)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	अक्षर क्षणिकe[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	पूर्णांक type = is_चयन ? HDA_CTL_WIDGET_MUTE : HDA_CTL_WIDGET_VOL;
	स्थिर अक्षर *sfx = is_चयन ? "Switch" : "Volume";
	अचिन्हित पूर्णांक chs = inv_dmic ? 1 : 3;
	काष्ठा snd_kcontrol_new *knew;

	अगर (!ctl)
		वापस 0;

	अगर (label)
		snम_लिखो(क्षणिकe, माप(क्षणिकe),
			 "%s Capture %s", label, sfx);
	अन्यथा
		snम_लिखो(क्षणिकe, माप(क्षणिकe),
			 "Capture %s", sfx);
	knew = add_control(spec, type, क्षणिकe, idx,
			   amp_val_replace_channels(ctl, chs));
	अगर (!knew)
		वापस -ENOMEM;
	अगर (is_चयन) अणु
		knew->put = cap_single_sw_put;
		अगर (spec->mic_mute_led)
			knew->access |= SNDRV_CTL_ELEM_ACCESS_MIC_LED;
	पूर्ण
	अगर (!inv_dmic)
		वापस 0;

	/* Make independent right kcontrol */
	अगर (label)
		snम_लिखो(क्षणिकe, माप(क्षणिकe),
			 "Inverted %s Capture %s", label, sfx);
	अन्यथा
		snम_लिखो(क्षणिकe, माप(क्षणिकe),
			 "Inverted Capture %s", sfx);
	knew = add_control(spec, type, क्षणिकe, idx,
			   amp_val_replace_channels(ctl, 2));
	अगर (!knew)
		वापस -ENOMEM;
	अगर (is_चयन) अणु
		knew->put = cap_single_sw_put;
		अगर (spec->mic_mute_led)
			knew->access |= SNDRV_CTL_ELEM_ACCESS_MIC_LED;
	पूर्ण
	वापस 0;
पूर्ण

/* create single (and simple) capture volume and चयन controls */
अटल पूर्णांक create_single_cap_vol_ctl(काष्ठा hda_codec *codec, पूर्णांक idx,
				     अचिन्हित पूर्णांक vol_ctl, अचिन्हित पूर्णांक sw_ctl,
				     bool inv_dmic)
अणु
	पूर्णांक err;
	err = add_single_cap_ctl(codec, शून्य, idx, false, vol_ctl, inv_dmic);
	अगर (err < 0)
		वापस err;
	err = add_single_cap_ctl(codec, शून्य, idx, true, sw_ctl, inv_dmic);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

/* create bound capture volume and चयन controls */
अटल पूर्णांक create_bind_cap_vol_ctl(काष्ठा hda_codec *codec, पूर्णांक idx,
				   अचिन्हित पूर्णांक vol_ctl, अचिन्हित पूर्णांक sw_ctl)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा snd_kcontrol_new *knew;

	अगर (vol_ctl) अणु
		knew = snd_hda_gen_add_kctl(spec, शून्य, &cap_vol_temp);
		अगर (!knew)
			वापस -ENOMEM;
		knew->index = idx;
		knew->निजी_value = vol_ctl;
		knew->subdevice = HDA_SUBDEV_AMP_FLAG;
	पूर्ण
	अगर (sw_ctl) अणु
		knew = snd_hda_gen_add_kctl(spec, शून्य, &cap_sw_temp);
		अगर (!knew)
			वापस -ENOMEM;
		knew->index = idx;
		knew->निजी_value = sw_ctl;
		knew->subdevice = HDA_SUBDEV_AMP_FLAG;
		अगर (spec->mic_mute_led)
			knew->access |= SNDRV_CTL_ELEM_ACCESS_MIC_LED;
	पूर्ण
	वापस 0;
पूर्ण

/* वापस the vol ctl when used first in the imux list */
अटल अचिन्हित पूर्णांक get_first_cap_ctl(काष्ठा hda_codec *codec, पूर्णांक idx, पूर्णांक type)
अणु
	काष्ठा nid_path *path;
	अचिन्हित पूर्णांक ctl;
	पूर्णांक i;

	path = get_input_path(codec, 0, idx);
	अगर (!path)
		वापस 0;
	ctl = path->ctls[type];
	अगर (!ctl)
		वापस 0;
	क्रम (i = 0; i < idx - 1; i++) अणु
		path = get_input_path(codec, 0, i);
		अगर (path && path->ctls[type] == ctl)
			वापस 0;
	पूर्ण
	वापस ctl;
पूर्ण

/* create inभागidual capture volume and चयन controls per input */
अटल पूर्णांक create_multi_cap_vol_ctl(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा hda_input_mux *imux = &spec->input_mux;
	पूर्णांक i, err, type;

	क्रम (i = 0; i < imux->num_items; i++) अणु
		bool inv_dmic;
		पूर्णांक idx;

		idx = imux->items[i].index;
		अगर (idx >= spec->स्वतःcfg.num_inमाला_दो)
			जारी;
		inv_dmic = is_inv_dmic_pin(codec, spec->imux_pins[i]);

		क्रम (type = 0; type < 2; type++) अणु
			err = add_single_cap_ctl(codec,
						 spec->input_labels[idx],
						 spec->input_label_idxs[idx],
						 type,
						 get_first_cap_ctl(codec, i, type),
						 inv_dmic);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक create_capture_mixers(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा hda_input_mux *imux = &spec->input_mux;
	पूर्णांक i, n, nums, err;

	अगर (spec->dyn_adc_चयन)
		nums = 1;
	अन्यथा
		nums = spec->num_adc_nids;

	अगर (!spec->स्वतः_mic && imux->num_items > 1) अणु
		काष्ठा snd_kcontrol_new *knew;
		स्थिर अक्षर *name;
		name = nums > 1 ? "Input Source" : "Capture Source";
		knew = snd_hda_gen_add_kctl(spec, name, &cap_src_temp);
		अगर (!knew)
			वापस -ENOMEM;
		knew->count = nums;
	पूर्ण

	क्रम (n = 0; n < nums; n++) अणु
		bool multi = false;
		bool multi_cap_vol = spec->multi_cap_vol;
		bool inv_dmic = false;
		पूर्णांक vol, sw;

		vol = sw = 0;
		क्रम (i = 0; i < imux->num_items; i++) अणु
			काष्ठा nid_path *path;
			path = get_input_path(codec, n, i);
			अगर (!path)
				जारी;
			parse_capvol_in_path(codec, path);
			अगर (!vol)
				vol = path->ctls[NID_PATH_VOL_CTL];
			अन्यथा अगर (vol != path->ctls[NID_PATH_VOL_CTL]) अणु
				multi = true;
				अगर (!same_amp_caps(codec, vol,
				    path->ctls[NID_PATH_VOL_CTL], HDA_INPUT))
					multi_cap_vol = true;
			पूर्ण
			अगर (!sw)
				sw = path->ctls[NID_PATH_MUTE_CTL];
			अन्यथा अगर (sw != path->ctls[NID_PATH_MUTE_CTL]) अणु
				multi = true;
				अगर (!same_amp_caps(codec, sw,
				    path->ctls[NID_PATH_MUTE_CTL], HDA_INPUT))
					multi_cap_vol = true;
			पूर्ण
			अगर (is_inv_dmic_pin(codec, spec->imux_pins[i]))
				inv_dmic = true;
		पूर्ण

		अगर (!multi)
			err = create_single_cap_vol_ctl(codec, n, vol, sw,
							inv_dmic);
		अन्यथा अगर (!multi_cap_vol && !inv_dmic)
			err = create_bind_cap_vol_ctl(codec, n, vol, sw);
		अन्यथा
			err = create_multi_cap_vol_ctl(codec);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * add mic boosts अगर needed
 */

/* check whether the given amp is feasible as a boost volume */
अटल bool check_boost_vol(काष्ठा hda_codec *codec, hda_nid_t nid,
			    पूर्णांक dir, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक step;

	अगर (!nid_has_volume(codec, nid, dir) ||
	    is_ctl_associated(codec, nid, dir, idx, NID_PATH_VOL_CTL) ||
	    is_ctl_associated(codec, nid, dir, idx, NID_PATH_BOOST_CTL))
		वापस false;

	step = (query_amp_caps(codec, nid, dir) & AC_AMPCAP_STEP_SIZE)
		>> AC_AMPCAP_STEP_SIZE_SHIFT;
	अगर (step < 0x20)
		वापस false;
	वापस true;
पूर्ण

/* look क्रम a boost amp in a widget बंद to the pin */
अटल अचिन्हित पूर्णांक look_क्रम_boost_amp(काष्ठा hda_codec *codec,
				       काष्ठा nid_path *path)
अणु
	अचिन्हित पूर्णांक val = 0;
	hda_nid_t nid;
	पूर्णांक depth;

	क्रम (depth = 0; depth < 3; depth++) अणु
		अगर (depth >= path->depth - 1)
			अवरोध;
		nid = path->path[depth];
		अगर (depth && check_boost_vol(codec, nid, HDA_OUTPUT, 0)) अणु
			val = HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_OUTPUT);
			अवरोध;
		पूर्ण अन्यथा अगर (check_boost_vol(codec, nid, HDA_INPUT,
					   path->idx[depth])) अणु
			val = HDA_COMPOSE_AMP_VAL(nid, 3, path->idx[depth],
						  HDA_INPUT);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक parse_mic_boost(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	काष्ठा hda_input_mux *imux = &spec->input_mux;
	पूर्णांक i;

	अगर (!spec->num_adc_nids)
		वापस 0;

	क्रम (i = 0; i < imux->num_items; i++) अणु
		काष्ठा nid_path *path;
		अचिन्हित पूर्णांक val;
		पूर्णांक idx;
		अक्षर boost_label[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];

		idx = imux->items[i].index;
		अगर (idx >= imux->num_items)
			जारी;

		/* check only line-in and mic pins */
		अगर (cfg->inमाला_दो[idx].type > AUTO_PIN_LINE_IN)
			जारी;

		path = get_input_path(codec, 0, i);
		अगर (!path)
			जारी;

		val = look_क्रम_boost_amp(codec, path);
		अगर (!val)
			जारी;

		/* create a boost control */
		snम_लिखो(boost_label, माप(boost_label),
			 "%s Boost Volume", spec->input_labels[idx]);
		अगर (!add_control(spec, HDA_CTL_WIDGET_VOL, boost_label,
				 spec->input_label_idxs[idx], val))
			वापस -ENOMEM;

		path->ctls[NID_PATH_BOOST_CTL] = val;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SND_HDA_GENERIC_LEDS
/*
 * vmaster mute LED hook helpers
 */

अटल पूर्णांक create_mute_led_cdev(काष्ठा hda_codec *codec,
				पूर्णांक (*callback)(काष्ठा led_classdev *,
						क्रमागत led_brightness),
				bool micmute)
अणु
	काष्ठा led_classdev *cdev;

	cdev = devm_kzalloc(&codec->core.dev, माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस -ENOMEM;

	cdev->name = micmute ? "hda::micmute" : "hda::mute";
	cdev->max_brightness = 1;
	cdev->शेष_trigger = micmute ? "audio-micmute" : "audio-mute";
	cdev->brightness_set_blocking = callback;
	cdev->brightness = ledtrig_audio_get(micmute ? LED_AUDIO_MICMUTE : LED_AUDIO_MUTE);
	cdev->flags = LED_CORE_SUSPENDRESUME;

	वापस devm_led_classdev_रेजिस्टर(&codec->core.dev, cdev);
पूर्ण

/**
 * snd_hda_gen_add_mute_led_cdev - Create a LED classdev and enable as vmaster mute LED
 * @codec: the HDA codec
 * @callback: the callback क्रम LED classdev brightness_set_blocking
 */
पूर्णांक snd_hda_gen_add_mute_led_cdev(काष्ठा hda_codec *codec,
				  पूर्णांक (*callback)(काष्ठा led_classdev *,
						  क्रमागत led_brightness))
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक err;

	अगर (callback) अणु
		err = create_mute_led_cdev(codec, callback, false);
		अगर (err) अणु
			codec_warn(codec, "failed to create a mute LED cdev\n");
			वापस err;
		पूर्ण
	पूर्ण

	अगर (spec->vmaster_mute.hook)
		codec_err(codec, "vmaster hook already present before cdev!\n");

	spec->vmaster_mute_led = 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_add_mute_led_cdev);

/**
 * snd_hda_gen_add_micmute_led_cdev - Create a LED classdev and enable as mic-mute LED
 * @codec: the HDA codec
 * @callback: the callback क्रम LED classdev brightness_set_blocking
 *
 * Called from the codec drivers क्रम offering the mic mute LED controls.
 * This creates a LED classdev and sets up the cap_sync_hook that is called at
 * each समय when the capture mixer चयन changes.
 *
 * When शून्य is passed to @callback, no classdev is created but only the
 * LED-trigger is set up.
 *
 * Returns 0 or a negative error.
 */
पूर्णांक snd_hda_gen_add_micmute_led_cdev(काष्ठा hda_codec *codec,
				     पूर्णांक (*callback)(काष्ठा led_classdev *,
						     क्रमागत led_brightness))
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक err;

	अगर (callback) अणु
		err = create_mute_led_cdev(codec, callback, true);
		अगर (err) अणु
			codec_warn(codec, "failed to create a mic-mute LED cdev\n");
			वापस err;
		पूर्ण
	पूर्ण

	spec->mic_mute_led = 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_add_micmute_led_cdev);
#पूर्ण_अगर /* CONFIG_SND_HDA_GENERIC_LEDS */

/*
 * parse digital I/Os and set up NIDs in BIOS स्वतः-parse mode
 */
अटल व्योम parse_digital(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा nid_path *path;
	पूर्णांक i, nums;
	hda_nid_t dig_nid, pin;

	/* support multiple SPDIFs; the secondary is set up as a follower */
	nums = 0;
	क्रम (i = 0; i < spec->स्वतःcfg.dig_outs; i++) अणु
		pin = spec->स्वतःcfg.dig_out_pins[i];
		dig_nid = look_क्रम_dac(codec, pin, true);
		अगर (!dig_nid)
			जारी;
		path = snd_hda_add_new_path(codec, dig_nid, pin, 0);
		अगर (!path)
			जारी;
		prपूर्णांक_nid_path(codec, "digout", path);
		path->active = true;
		path->pin_fixed = true; /* no jack detection */
		spec->digout_paths[i] = snd_hda_get_path_idx(codec, path);
		set_pin_target(codec, pin, PIN_OUT, false);
		अगर (!nums) अणु
			spec->multiout.dig_out_nid = dig_nid;
			spec->dig_out_type = spec->स्वतःcfg.dig_out_type[0];
		पूर्ण अन्यथा अणु
			spec->multiout.follower_dig_outs = spec->follower_dig_outs;
			अगर (nums >= ARRAY_SIZE(spec->follower_dig_outs) - 1)
				अवरोध;
			spec->follower_dig_outs[nums - 1] = dig_nid;
		पूर्ण
		nums++;
	पूर्ण

	अगर (spec->स्वतःcfg.dig_in_pin) अणु
		pin = spec->स्वतःcfg.dig_in_pin;
		क्रम_each_hda_codec_node(dig_nid, codec) अणु
			अचिन्हित पूर्णांक wcaps = get_wcaps(codec, dig_nid);
			अगर (get_wcaps_type(wcaps) != AC_WID_AUD_IN)
				जारी;
			अगर (!(wcaps & AC_WCAP_DIGITAL))
				जारी;
			path = snd_hda_add_new_path(codec, pin, dig_nid, 0);
			अगर (path) अणु
				prपूर्णांक_nid_path(codec, "digin", path);
				path->active = true;
				path->pin_fixed = true; /* no jack */
				spec->dig_in_nid = dig_nid;
				spec->digin_path = snd_hda_get_path_idx(codec, path);
				set_pin_target(codec, pin, PIN_IN, false);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


/*
 * input MUX handling
 */

अटल bool dyn_adc_pcm_resetup(काष्ठा hda_codec *codec, पूर्णांक cur);

/* select the given imux item; either unmute exclusively or select the route */
अटल पूर्णांक mux_select(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक adc_idx,
		      अचिन्हित पूर्णांक idx)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	स्थिर काष्ठा hda_input_mux *imux;
	काष्ठा nid_path *old_path, *path;

	imux = &spec->input_mux;
	अगर (!imux->num_items)
		वापस 0;

	अगर (idx >= imux->num_items)
		idx = imux->num_items - 1;
	अगर (spec->cur_mux[adc_idx] == idx)
		वापस 0;

	old_path = get_input_path(codec, adc_idx, spec->cur_mux[adc_idx]);
	अगर (!old_path)
		वापस 0;
	अगर (old_path->active)
		snd_hda_activate_path(codec, old_path, false, false);

	spec->cur_mux[adc_idx] = idx;

	अगर (spec->hp_mic)
		update_hp_mic(codec, adc_idx, false);

	अगर (spec->dyn_adc_चयन)
		dyn_adc_pcm_resetup(codec, idx);

	path = get_input_path(codec, adc_idx, idx);
	अगर (!path)
		वापस 0;
	अगर (path->active)
		वापस 0;
	snd_hda_activate_path(codec, path, true, false);
	अगर (spec->cap_sync_hook)
		spec->cap_sync_hook(codec, शून्य, शून्य);
	path_घातer_करोwn_sync(codec, old_path);
	वापस 1;
पूर्ण

/* घातer up/करोwn widमाला_लो in the all paths that match with the given NID
 * as terminals (either start- or endpoपूर्णांक)
 *
 * वापसs the last changed NID, or zero अगर unchanged.
 */
अटल hda_nid_t set_path_घातer(काष्ठा hda_codec *codec, hda_nid_t nid,
				पूर्णांक pin_state, पूर्णांक stream_state)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	hda_nid_t last, changed = 0;
	काष्ठा nid_path *path;
	पूर्णांक n;

	snd_array_क्रम_each(&spec->paths, n, path) अणु
		अगर (!path->depth)
			जारी;
		अगर (path->path[0] == nid ||
		    path->path[path->depth - 1] == nid) अणु
			bool pin_old = path->pin_enabled;
			bool stream_old = path->stream_enabled;

			अगर (pin_state >= 0)
				path->pin_enabled = pin_state;
			अगर (stream_state >= 0)
				path->stream_enabled = stream_state;
			अगर ((!path->pin_fixed && path->pin_enabled != pin_old)
			    || path->stream_enabled != stream_old) अणु
				last = path_घातer_update(codec, path, true);
				अगर (last)
					changed = last;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस changed;
पूर्ण

/* check the jack status क्रम घातer control */
अटल bool detect_pin_state(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	अगर (!is_jack_detectable(codec, pin))
		वापस true;
	वापस snd_hda_jack_detect_state(codec, pin) != HDA_JACK_NOT_PRESENT;
पूर्ण

/* घातer up/करोwn the paths of the given pin according to the jack state;
 * घातer = 0/1 : only घातer up/करोwn अगर it matches with the jack state,
 *       < 0   : क्रमce घातer up/करोwn to follow the jack sate
 *
 * वापसs the last changed NID, or zero अगर unchanged.
 */
अटल hda_nid_t set_pin_घातer_jack(काष्ठा hda_codec *codec, hda_nid_t pin,
				    पूर्णांक घातer)
अणु
	bool on;

	अगर (!codec->घातer_save_node)
		वापस 0;

	on = detect_pin_state(codec, pin);

	अगर (घातer >= 0 && on != घातer)
		वापस 0;
	वापस set_path_घातer(codec, pin, on, -1);
पूर्ण

अटल व्योम pin_घातer_callback(काष्ठा hda_codec *codec,
			       काष्ठा hda_jack_callback *jack,
			       bool on)
अणु
	अगर (jack && jack->nid)
		sync_घातer_state_change(codec,
					set_pin_घातer_jack(codec, jack->nid, on));
पूर्ण

/* callback only करोing घातer up -- called at first */
अटल व्योम pin_घातer_up_callback(काष्ठा hda_codec *codec,
				  काष्ठा hda_jack_callback *jack)
अणु
	pin_घातer_callback(codec, jack, true);
पूर्ण

/* callback only करोing घातer करोwn -- called at last */
अटल व्योम pin_घातer_करोwn_callback(काष्ठा hda_codec *codec,
				    काष्ठा hda_jack_callback *jack)
अणु
	pin_घातer_callback(codec, jack, false);
पूर्ण

/* set up the घातer up/करोwn callbacks */
अटल व्योम add_pin_घातer_ctls(काष्ठा hda_codec *codec, पूर्णांक num_pins,
			       स्थिर hda_nid_t *pins, bool on)
अणु
	पूर्णांक i;
	hda_jack_callback_fn cb =
		on ? pin_घातer_up_callback : pin_घातer_करोwn_callback;

	क्रम (i = 0; i < num_pins && pins[i]; i++) अणु
		अगर (is_jack_detectable(codec, pins[i]))
			snd_hda_jack_detect_enable_callback(codec, pins[i], cb);
		अन्यथा
			set_path_घातer(codec, pins[i], true, -1);
	पूर्ण
पूर्ण

/* enabled घातer callback to each available I/O pin with jack detections;
 * the digital I/O pins are excluded because of the unreliable detectsion
 */
अटल व्योम add_all_pin_घातer_ctls(काष्ठा hda_codec *codec, bool on)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	पूर्णांक i;

	अगर (!codec->घातer_save_node)
		वापस;
	add_pin_घातer_ctls(codec, cfg->line_outs, cfg->line_out_pins, on);
	अगर (cfg->line_out_type != AUTO_PIN_HP_OUT)
		add_pin_घातer_ctls(codec, cfg->hp_outs, cfg->hp_pins, on);
	अगर (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT)
		add_pin_घातer_ctls(codec, cfg->speaker_outs, cfg->speaker_pins, on);
	क्रम (i = 0; i < cfg->num_inमाला_दो; i++)
		add_pin_घातer_ctls(codec, 1, &cfg->inमाला_दो[i].pin, on);
पूर्ण

/* sync path घातer up/करोwn with the jack states of given pins */
अटल व्योम sync_pin_घातer_ctls(काष्ठा hda_codec *codec, पूर्णांक num_pins,
				स्थिर hda_nid_t *pins)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_pins && pins[i]; i++)
		अगर (is_jack_detectable(codec, pins[i]))
			set_pin_घातer_jack(codec, pins[i], -1);
पूर्ण

/* sync path घातer up/करोwn with pins; called at init and resume */
अटल व्योम sync_all_pin_घातer_ctls(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	पूर्णांक i;

	अगर (!codec->घातer_save_node)
		वापस;
	sync_pin_घातer_ctls(codec, cfg->line_outs, cfg->line_out_pins);
	अगर (cfg->line_out_type != AUTO_PIN_HP_OUT)
		sync_pin_घातer_ctls(codec, cfg->hp_outs, cfg->hp_pins);
	अगर (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT)
		sync_pin_घातer_ctls(codec, cfg->speaker_outs, cfg->speaker_pins);
	क्रम (i = 0; i < cfg->num_inमाला_दो; i++)
		sync_pin_घातer_ctls(codec, 1, &cfg->inमाला_दो[i].pin);
पूर्ण

/* add fake paths अगर not present yet */
अटल पूर्णांक add_fake_paths(काष्ठा hda_codec *codec, hda_nid_t nid,
			   पूर्णांक num_pins, स्थिर hda_nid_t *pins)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा nid_path *path;
	पूर्णांक i;

	क्रम (i = 0; i < num_pins; i++) अणु
		अगर (!pins[i])
			अवरोध;
		अगर (get_nid_path(codec, nid, pins[i], 0))
			जारी;
		path = snd_array_new(&spec->paths);
		अगर (!path)
			वापस -ENOMEM;
		स_रखो(path, 0, माप(*path));
		path->depth = 2;
		path->path[0] = nid;
		path->path[1] = pins[i];
		path->active = true;
	पूर्ण
	वापस 0;
पूर्ण

/* create fake paths to all outमाला_दो from beep */
अटल पूर्णांक add_fake_beep_paths(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	hda_nid_t nid = spec->beep_nid;
	पूर्णांक err;

	अगर (!codec->घातer_save_node || !nid)
		वापस 0;
	err = add_fake_paths(codec, nid, cfg->line_outs, cfg->line_out_pins);
	अगर (err < 0)
		वापस err;
	अगर (cfg->line_out_type != AUTO_PIN_HP_OUT) अणु
		err = add_fake_paths(codec, nid, cfg->hp_outs, cfg->hp_pins);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT) अणु
		err = add_fake_paths(codec, nid, cfg->speaker_outs,
				     cfg->speaker_pins);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* घातer up/करोwn beep widget and its output paths */
अटल व्योम beep_घातer_hook(काष्ठा hda_beep *beep, bool on)
अणु
	set_path_घातer(beep->codec, beep->nid, -1, on);
पूर्ण

/**
 * snd_hda_gen_fix_pin_घातer - Fix the घातer of the given pin widget to D0
 * @codec: the HDA codec
 * @pin: NID of pin to fix
 */
पूर्णांक snd_hda_gen_fix_pin_घातer(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा nid_path *path;

	path = snd_array_new(&spec->paths);
	अगर (!path)
		वापस -ENOMEM;
	स_रखो(path, 0, माप(*path));
	path->depth = 1;
	path->path[0] = pin;
	path->active = true;
	path->pin_fixed = true;
	path->stream_enabled = true;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_fix_pin_घातer);

/*
 * Jack detections क्रम HP स्वतः-mute and mic-चयन
 */

/* check each pin in the given array; वापसs true अगर any of them is plugged */
अटल bool detect_jacks(काष्ठा hda_codec *codec, पूर्णांक num_pins, स्थिर hda_nid_t *pins)
अणु
	पूर्णांक i;
	bool present = false;

	क्रम (i = 0; i < num_pins; i++) अणु
		hda_nid_t nid = pins[i];
		अगर (!nid)
			अवरोध;
		/* करोn't detect pins retasked as inमाला_दो */
		अगर (snd_hda_codec_get_pin_target(codec, nid) & AC_PINCTL_IN_EN)
			जारी;
		अगर (snd_hda_jack_detect_state(codec, nid) == HDA_JACK_PRESENT)
			present = true;
	पूर्ण
	वापस present;
पूर्ण

/* standard HP/line-out स्वतः-mute helper */
अटल व्योम करो_स्वतःmute(काष्ठा hda_codec *codec, पूर्णांक num_pins, स्थिर hda_nid_t *pins,
			पूर्णांक *paths, bool mute)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i;

	क्रम (i = 0; i < num_pins; i++) अणु
		hda_nid_t nid = pins[i];
		अचिन्हित पूर्णांक val, oldval;
		अगर (!nid)
			अवरोध;

		oldval = snd_hda_codec_get_pin_target(codec, nid);
		अगर (oldval & PIN_IN)
			जारी; /* no mute क्रम inमाला_दो */

		अगर (spec->स्वतः_mute_via_amp) अणु
			काष्ठा nid_path *path;
			hda_nid_t mute_nid;

			path = snd_hda_get_path_from_idx(codec, paths[i]);
			अगर (!path)
				जारी;
			mute_nid = get_amp_nid_(path->ctls[NID_PATH_MUTE_CTL]);
			अगर (!mute_nid)
				जारी;
			अगर (mute)
				spec->mute_bits |= (1ULL << mute_nid);
			अन्यथा
				spec->mute_bits &= ~(1ULL << mute_nid);
			जारी;
		पूर्ण अन्यथा अणु
			/* करोn't reset VREF value in case it's controlling
			 * the amp (see alc861_fixup_asus_amp_vref_0f())
			 */
			अगर (spec->keep_vref_in_स्वतःmute)
				val = oldval & ~PIN_HP;
			अन्यथा
				val = 0;
			अगर (!mute)
				val |= oldval;
			/* here we call update_pin_ctl() so that the pinctl is
			 * changed without changing the pinctl target value;
			 * the original target value will be still referred at
			 * the init / resume again
			 */
			update_pin_ctl(codec, nid, val);
		पूर्ण

		set_pin_eapd(codec, nid, !mute);
		अगर (codec->घातer_save_node) अणु
			bool on = !mute;
			अगर (on)
				on = detect_pin_state(codec, nid);
			set_path_घातer(codec, nid, on, -1);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * snd_hda_gen_update_outमाला_दो - Toggle outमाला_दो muting
 * @codec: the HDA codec
 *
 * Update the mute status of all outमाला_दो based on the current jack states.
 */
व्योम snd_hda_gen_update_outमाला_दो(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक *paths;
	पूर्णांक on;

	/* Control HP pins/amps depending on master_mute state;
	 * in general, HP pins/amps control should be enabled in all हालs,
	 * but currently set only क्रम master_mute, just to be safe
	 */
	अगर (spec->स्वतःcfg.line_out_type == AUTO_PIN_HP_OUT)
		paths = spec->out_paths;
	अन्यथा
		paths = spec->hp_paths;
	करो_स्वतःmute(codec, ARRAY_SIZE(spec->स्वतःcfg.hp_pins),
		    spec->स्वतःcfg.hp_pins, paths, spec->master_mute);

	अगर (!spec->स्वतःmute_speaker)
		on = 0;
	अन्यथा
		on = spec->hp_jack_present | spec->line_jack_present;
	on |= spec->master_mute;
	spec->speaker_muted = on;
	अगर (spec->स्वतःcfg.line_out_type == AUTO_PIN_SPEAKER_OUT)
		paths = spec->out_paths;
	अन्यथा
		paths = spec->speaker_paths;
	करो_स्वतःmute(codec, ARRAY_SIZE(spec->स्वतःcfg.speaker_pins),
		    spec->स्वतःcfg.speaker_pins, paths, on);

	/* toggle line-out mutes अगर needed, too */
	/* अगर LO is a copy of either HP or Speaker, करोn't need to handle it */
	अगर (spec->स्वतःcfg.line_out_pins[0] == spec->स्वतःcfg.hp_pins[0] ||
	    spec->स्वतःcfg.line_out_pins[0] == spec->स्वतःcfg.speaker_pins[0])
		वापस;
	अगर (!spec->स्वतःmute_lo)
		on = 0;
	अन्यथा
		on = spec->hp_jack_present;
	on |= spec->master_mute;
	spec->line_out_muted = on;
	paths = spec->out_paths;
	करो_स्वतःmute(codec, ARRAY_SIZE(spec->स्वतःcfg.line_out_pins),
		    spec->स्वतःcfg.line_out_pins, paths, on);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_update_outमाला_दो);

अटल व्योम call_update_outमाला_दो(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	अगर (spec->स्वतःmute_hook)
		spec->स्वतःmute_hook(codec);
	अन्यथा
		snd_hda_gen_update_outमाला_दो(codec);

	/* sync the whole vmaster followers to reflect the new स्वतः-mute status */
	अगर (spec->स्वतः_mute_via_amp && !codec->bus->shutकरोwn)
		snd_ctl_sync_vmaster(spec->vmaster_mute.sw_kctl, false);
पूर्ण

/**
 * snd_hda_gen_hp_स्वतःmute - standard HP-स्वतःmute helper
 * @codec: the HDA codec
 * @jack: jack object, शून्य क्रम the whole
 */
व्योम snd_hda_gen_hp_स्वतःmute(काष्ठा hda_codec *codec,
			     काष्ठा hda_jack_callback *jack)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	hda_nid_t *pins = spec->स्वतःcfg.hp_pins;
	पूर्णांक num_pins = ARRAY_SIZE(spec->स्वतःcfg.hp_pins);

	/* No detection क्रम the first HP jack during indep-HP mode */
	अगर (spec->indep_hp_enabled) अणु
		pins++;
		num_pins--;
	पूर्ण

	spec->hp_jack_present = detect_jacks(codec, num_pins, pins);
	अगर (!spec->detect_hp || (!spec->स्वतःmute_speaker && !spec->स्वतःmute_lo))
		वापस;
	call_update_outमाला_दो(codec);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_hp_स्वतःmute);

/**
 * snd_hda_gen_line_स्वतःmute - standard line-out-स्वतःmute helper
 * @codec: the HDA codec
 * @jack: jack object, शून्य क्रम the whole
 */
व्योम snd_hda_gen_line_स्वतःmute(काष्ठा hda_codec *codec,
			       काष्ठा hda_jack_callback *jack)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;

	अगर (spec->स्वतःcfg.line_out_type == AUTO_PIN_SPEAKER_OUT)
		वापस;
	/* check LO jack only when it's dअगरferent from HP */
	अगर (spec->स्वतःcfg.line_out_pins[0] == spec->स्वतःcfg.hp_pins[0])
		वापस;

	spec->line_jack_present =
		detect_jacks(codec, ARRAY_SIZE(spec->स्वतःcfg.line_out_pins),
			     spec->स्वतःcfg.line_out_pins);
	अगर (!spec->स्वतःmute_speaker || !spec->detect_lo)
		वापस;
	call_update_outमाला_दो(codec);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_line_स्वतःmute);

/**
 * snd_hda_gen_mic_स्वतःचयन - standard mic स्वतः-चयन helper
 * @codec: the HDA codec
 * @jack: jack object, शून्य क्रम the whole
 */
व्योम snd_hda_gen_mic_स्वतःचयन(काष्ठा hda_codec *codec,
				काष्ठा hda_jack_callback *jack)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i;

	अगर (!spec->स्वतः_mic)
		वापस;

	क्रम (i = spec->am_num_entries - 1; i > 0; i--) अणु
		hda_nid_t pin = spec->am_entry[i].pin;
		/* करोn't detect pins retasked as outमाला_दो */
		अगर (snd_hda_codec_get_pin_target(codec, pin) & AC_PINCTL_OUT_EN)
			जारी;
		अगर (snd_hda_jack_detect_state(codec, pin) == HDA_JACK_PRESENT) अणु
			mux_select(codec, 0, spec->am_entry[i].idx);
			वापस;
		पूर्ण
	पूर्ण
	mux_select(codec, 0, spec->am_entry[0].idx);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_mic_स्वतःचयन);

/* call appropriate hooks */
अटल व्योम call_hp_स्वतःmute(काष्ठा hda_codec *codec,
			     काष्ठा hda_jack_callback *jack)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	अगर (spec->hp_स्वतःmute_hook)
		spec->hp_स्वतःmute_hook(codec, jack);
	अन्यथा
		snd_hda_gen_hp_स्वतःmute(codec, jack);
पूर्ण

अटल व्योम call_line_स्वतःmute(काष्ठा hda_codec *codec,
			       काष्ठा hda_jack_callback *jack)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	अगर (spec->line_स्वतःmute_hook)
		spec->line_स्वतःmute_hook(codec, jack);
	अन्यथा
		snd_hda_gen_line_स्वतःmute(codec, jack);
पूर्ण

अटल व्योम call_mic_स्वतःचयन(काष्ठा hda_codec *codec,
				काष्ठा hda_jack_callback *jack)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	अगर (spec->mic_स्वतःचयन_hook)
		spec->mic_स्वतःचयन_hook(codec, jack);
	अन्यथा
		snd_hda_gen_mic_स्वतःचयन(codec, jack);
पूर्ण

/* update jack retasking */
अटल व्योम update_स्वतःmute_all(काष्ठा hda_codec *codec)
अणु
	call_hp_स्वतःmute(codec, शून्य);
	call_line_स्वतःmute(codec, शून्य);
	call_mic_स्वतःचयन(codec, शून्य);
पूर्ण

/*
 * Auto-Mute mode mixer क्रमागत support
 */
अटल पूर्णांक स्वतःmute_mode_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	अटल स्थिर अक्षर * स्थिर texts3[] = अणु
		"Disabled", "Speaker Only", "Line Out+Speaker"
	पूर्ण;

	अगर (spec->स्वतःmute_speaker_possible && spec->स्वतःmute_lo_possible)
		वापस snd_hda_क्रमागत_helper_info(kcontrol, uinfo, 3, texts3);
	वापस snd_hda_क्रमागत_bool_helper_info(kcontrol, uinfo);
पूर्ण

अटल पूर्णांक स्वतःmute_mode_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;
	अचिन्हित पूर्णांक val = 0;
	अगर (spec->स्वतःmute_speaker)
		val++;
	अगर (spec->स्वतःmute_lo)
		val++;

	ucontrol->value.क्रमागतerated.item[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक स्वतःmute_mode_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_gen_spec *spec = codec->spec;

	चयन (ucontrol->value.क्रमागतerated.item[0]) अणु
	हाल 0:
		अगर (!spec->स्वतःmute_speaker && !spec->स्वतःmute_lo)
			वापस 0;
		spec->स्वतःmute_speaker = 0;
		spec->स्वतःmute_lo = 0;
		अवरोध;
	हाल 1:
		अगर (spec->स्वतःmute_speaker_possible) अणु
			अगर (!spec->स्वतःmute_lo && spec->स्वतःmute_speaker)
				वापस 0;
			spec->स्वतःmute_speaker = 1;
			spec->स्वतःmute_lo = 0;
		पूर्ण अन्यथा अगर (spec->स्वतःmute_lo_possible) अणु
			अगर (spec->स्वतःmute_lo)
				वापस 0;
			spec->स्वतःmute_lo = 1;
		पूर्ण अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल 2:
		अगर (!spec->स्वतःmute_lo_possible || !spec->स्वतःmute_speaker_possible)
			वापस -EINVAL;
		अगर (spec->स्वतःmute_speaker && spec->स्वतःmute_lo)
			वापस 0;
		spec->स्वतःmute_speaker = 1;
		spec->स्वतःmute_lo = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	call_update_outमाला_दो(codec);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new स्वतःmute_mode_क्रमागत = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Auto-Mute Mode",
	.info = स्वतःmute_mode_info,
	.get = स्वतःmute_mode_get,
	.put = स्वतःmute_mode_put,
पूर्ण;

अटल पूर्णांक add_स्वतःmute_mode_क्रमागत(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;

	अगर (!snd_hda_gen_add_kctl(spec, शून्य, &स्वतःmute_mode_क्रमागत))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/*
 * Check the availability of HP/line-out स्वतः-mute;
 * Set up appropriately अगर really supported
 */
अटल पूर्णांक check_स्वतः_mute_availability(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	पूर्णांक present = 0;
	पूर्णांक i, err;

	अगर (spec->suppress_स्वतः_mute)
		वापस 0;

	अगर (cfg->hp_pins[0])
		present++;
	अगर (cfg->line_out_pins[0])
		present++;
	अगर (cfg->speaker_pins[0])
		present++;
	अगर (present < 2) /* need two dअगरferent output types */
		वापस 0;

	अगर (!cfg->speaker_pins[0] &&
	    cfg->line_out_type == AUTO_PIN_SPEAKER_OUT) अणु
		स_नकल(cfg->speaker_pins, cfg->line_out_pins,
		       माप(cfg->speaker_pins));
		cfg->speaker_outs = cfg->line_outs;
	पूर्ण

	अगर (!cfg->hp_pins[0] &&
	    cfg->line_out_type == AUTO_PIN_HP_OUT) अणु
		स_नकल(cfg->hp_pins, cfg->line_out_pins,
		       माप(cfg->hp_pins));
		cfg->hp_outs = cfg->line_outs;
	पूर्ण

	क्रम (i = 0; i < cfg->hp_outs; i++) अणु
		hda_nid_t nid = cfg->hp_pins[i];
		अगर (!is_jack_detectable(codec, nid))
			जारी;
		codec_dbg(codec, "Enable HP auto-muting on NID 0x%x\n", nid);
		snd_hda_jack_detect_enable_callback(codec, nid,
						    call_hp_स्वतःmute);
		spec->detect_hp = 1;
	पूर्ण

	अगर (cfg->line_out_type == AUTO_PIN_LINE_OUT && cfg->line_outs) अणु
		अगर (cfg->speaker_outs)
			क्रम (i = 0; i < cfg->line_outs; i++) अणु
				hda_nid_t nid = cfg->line_out_pins[i];
				अगर (!is_jack_detectable(codec, nid))
					जारी;
				codec_dbg(codec, "Enable Line-Out auto-muting on NID 0x%x\n", nid);
				snd_hda_jack_detect_enable_callback(codec, nid,
								    call_line_स्वतःmute);
				spec->detect_lo = 1;
			पूर्ण
		spec->स्वतःmute_lo_possible = spec->detect_hp;
	पूर्ण

	spec->स्वतःmute_speaker_possible = cfg->speaker_outs &&
		(spec->detect_hp || spec->detect_lo);

	spec->स्वतःmute_lo = spec->स्वतःmute_lo_possible;
	spec->स्वतःmute_speaker = spec->स्वतःmute_speaker_possible;

	अगर (spec->स्वतःmute_speaker_possible || spec->स्वतःmute_lo_possible) अणु
		/* create a control क्रम स्वतःmute mode */
		err = add_स्वतःmute_mode_क्रमागत(codec);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* check whether all स्वतः-mic pins are valid; setup indices अगर OK */
अटल bool स्वतः_mic_check_imux(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	स्थिर काष्ठा hda_input_mux *imux;
	पूर्णांक i;

	imux = &spec->input_mux;
	क्रम (i = 0; i < spec->am_num_entries; i++) अणु
		spec->am_entry[i].idx =
			find_idx_in_nid_list(spec->am_entry[i].pin,
					     spec->imux_pins, imux->num_items);
		अगर (spec->am_entry[i].idx < 0)
			वापस false; /* no corresponding imux */
	पूर्ण

	/* we करोn't need the jack detection क्रम the first pin */
	क्रम (i = 1; i < spec->am_num_entries; i++)
		snd_hda_jack_detect_enable_callback(codec,
						    spec->am_entry[i].pin,
						    call_mic_स्वतःचयन);
	वापस true;
पूर्ण

अटल पूर्णांक compare_attr(स्थिर व्योम *ap, स्थिर व्योम *bp)
अणु
	स्थिर काष्ठा स्वतःmic_entry *a = ap;
	स्थिर काष्ठा स्वतःmic_entry *b = bp;
	वापस (पूर्णांक)(a->attr - b->attr);
पूर्ण

/*
 * Check the availability of स्वतः-mic चयन;
 * Set up अगर really supported
 */
अटल पूर्णांक check_स्वतः_mic_availability(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	अचिन्हित पूर्णांक types;
	पूर्णांक i, num_pins;

	अगर (spec->suppress_स्वतः_mic)
		वापस 0;

	types = 0;
	num_pins = 0;
	क्रम (i = 0; i < cfg->num_inमाला_दो; i++) अणु
		hda_nid_t nid = cfg->inमाला_दो[i].pin;
		अचिन्हित पूर्णांक attr;
		attr = snd_hda_codec_get_pincfg(codec, nid);
		attr = snd_hda_get_input_pin_attr(attr);
		अगर (types & (1 << attr))
			वापस 0; /* alपढ़ोy occupied */
		चयन (attr) अणु
		हाल INPUT_PIN_ATTR_INT:
			अगर (cfg->inमाला_दो[i].type != AUTO_PIN_MIC)
				वापस 0; /* invalid type */
			अवरोध;
		हाल INPUT_PIN_ATTR_UNUSED:
			वापस 0; /* invalid entry */
		शेष:
			अगर (cfg->inमाला_दो[i].type > AUTO_PIN_LINE_IN)
				वापस 0; /* invalid type */
			अगर (!spec->line_in_स्वतः_चयन &&
			    cfg->inमाला_दो[i].type != AUTO_PIN_MIC)
				वापस 0; /* only mic is allowed */
			अगर (!is_jack_detectable(codec, nid))
				वापस 0; /* no unsol support */
			अवरोध;
		पूर्ण
		अगर (num_pins >= MAX_AUTO_MIC_PINS)
			वापस 0;
		types |= (1 << attr);
		spec->am_entry[num_pins].pin = nid;
		spec->am_entry[num_pins].attr = attr;
		num_pins++;
	पूर्ण

	अगर (num_pins < 2)
		वापस 0;

	spec->am_num_entries = num_pins;
	/* sort the am_entry in the order of attr so that the pin with a
	 * higher attr will be selected when the jack is plugged.
	 */
	sort(spec->am_entry, num_pins, माप(spec->am_entry[0]),
	     compare_attr, शून्य);

	अगर (!स्वतः_mic_check_imux(codec))
		वापस 0;

	spec->स्वतः_mic = 1;
	spec->num_adc_nids = 1;
	spec->cur_mux[0] = spec->am_entry[0].idx;
	codec_dbg(codec, "Enable auto-mic switch on NID 0x%x/0x%x/0x%x\n",
		    spec->am_entry[0].pin,
		    spec->am_entry[1].pin,
		    spec->am_entry[2].pin);

	वापस 0;
पूर्ण

/**
 * snd_hda_gen_path_घातer_filter - घातer_filter hook to make inactive widमाला_लो
 * पूर्णांकo घातer करोwn
 * @codec: the HDA codec
 * @nid: NID to evalute
 * @घातer_state: target घातer state
 */
अचिन्हित पूर्णांक snd_hda_gen_path_घातer_filter(काष्ठा hda_codec *codec,
						  hda_nid_t nid,
						  अचिन्हित पूर्णांक घातer_state)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;

	अगर (!spec->घातer_करोwn_unused && !codec->घातer_save_node)
		वापस घातer_state;
	अगर (घातer_state != AC_PWRST_D0 || nid == codec->core.afg)
		वापस घातer_state;
	अगर (get_wcaps_type(get_wcaps(codec, nid)) >= AC_WID_POWER)
		वापस घातer_state;
	अगर (is_active_nid_क्रम_any(codec, nid))
		वापस घातer_state;
	वापस AC_PWRST_D3;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_path_घातer_filter);

/* mute all aamix inमाला_दो initially; parse up to the first leaves */
अटल व्योम mute_all_mixer_nid(काष्ठा hda_codec *codec, hda_nid_t mix)
अणु
	पूर्णांक i, nums;
	स्थिर hda_nid_t *conn;
	bool has_amp;

	nums = snd_hda_get_conn_list(codec, mix, &conn);
	has_amp = nid_has_mute(codec, mix, HDA_INPUT);
	क्रम (i = 0; i < nums; i++) अणु
		अगर (has_amp)
			update_amp(codec, mix, HDA_INPUT, i,
				   0xff, HDA_AMP_MUTE);
		अन्यथा अगर (nid_has_volume(codec, conn[i], HDA_OUTPUT))
			update_amp(codec, conn[i], HDA_OUTPUT, 0,
				   0xff, HDA_AMP_MUTE);
	पूर्ण
पूर्ण

/**
 * snd_hda_gen_stream_pm - Stream घातer management callback
 * @codec: the HDA codec
 * @nid: audio widget
 * @on: घातer on/off flag
 *
 * Set this in patch_ops.stream_pm.  Only valid with घातer_save_node flag.
 */
व्योम snd_hda_gen_stream_pm(काष्ठा hda_codec *codec, hda_nid_t nid, bool on)
अणु
	अगर (codec->घातer_save_node)
		set_path_घातer(codec, nid, -1, on);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_stream_pm);

/**
 * snd_hda_gen_parse_स्वतः_config - Parse the given BIOS configuration and
 * set up the hda_gen_spec
 * @codec: the HDA codec
 * @cfg: Parsed pin configuration
 *
 * वापस 1 अगर successful, 0 अगर the proper config is not found,
 * or a negative error code
 */
पूर्णांक snd_hda_gen_parse_स्वतः_config(काष्ठा hda_codec *codec,
				  काष्ठा स्वतः_pin_cfg *cfg)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक err;

	parse_user_hपूर्णांकs(codec);

	अगर (spec->vmaster_mute_led || spec->mic_mute_led)
		snd_ctl_led_request();

	अगर (spec->mixer_nid && !spec->mixer_merge_nid)
		spec->mixer_merge_nid = spec->mixer_nid;

	अगर (cfg != &spec->स्वतःcfg) अणु
		spec->स्वतःcfg = *cfg;
		cfg = &spec->स्वतःcfg;
	पूर्ण

	अगर (!spec->मुख्य_out_badness)
		spec->मुख्य_out_badness = &hda_मुख्य_out_badness;
	अगर (!spec->extra_out_badness)
		spec->extra_out_badness = &hda_extra_out_badness;

	fill_all_dac_nids(codec);

	अगर (!cfg->line_outs) अणु
		अगर (cfg->dig_outs || cfg->dig_in_pin) अणु
			spec->multiout.max_channels = 2;
			spec->no_analog = 1;
			जाओ dig_only;
		पूर्ण
		अगर (!cfg->num_inमाला_दो && !cfg->dig_in_pin)
			वापस 0; /* can't find valid BIOS pin config */
	पूर्ण

	अगर (!spec->no_primary_hp &&
	    cfg->line_out_type == AUTO_PIN_SPEAKER_OUT &&
	    cfg->line_outs <= cfg->hp_outs) अणु
		/* use HP as primary out */
		cfg->speaker_outs = cfg->line_outs;
		स_नकल(cfg->speaker_pins, cfg->line_out_pins,
		       माप(cfg->speaker_pins));
		cfg->line_outs = cfg->hp_outs;
		स_नकल(cfg->line_out_pins, cfg->hp_pins, माप(cfg->hp_pins));
		cfg->hp_outs = 0;
		स_रखो(cfg->hp_pins, 0, माप(cfg->hp_pins));
		cfg->line_out_type = AUTO_PIN_HP_OUT;
	पूर्ण

	err = parse_output_paths(codec);
	अगर (err < 0)
		वापस err;
	err = create_multi_channel_mode(codec);
	अगर (err < 0)
		वापस err;
	err = create_multi_out_ctls(codec, cfg);
	अगर (err < 0)
		वापस err;
	err = create_hp_out_ctls(codec);
	अगर (err < 0)
		वापस err;
	err = create_speaker_out_ctls(codec);
	अगर (err < 0)
		वापस err;
	err = create_indep_hp_ctls(codec);
	अगर (err < 0)
		वापस err;
	err = create_loopback_mixing_ctl(codec);
	अगर (err < 0)
		वापस err;
	err = create_hp_mic(codec);
	अगर (err < 0)
		वापस err;
	err = create_input_ctls(codec);
	अगर (err < 0)
		वापस err;

	/* add घातer-करोwn pin callbacks at first */
	add_all_pin_घातer_ctls(codec, false);

	spec->स्थिर_channel_count = spec->ext_channel_count;
	/* check the multiple speaker and headphone pins */
	अगर (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT)
		spec->स्थिर_channel_count = max(spec->स्थिर_channel_count,
						cfg->speaker_outs * 2);
	अगर (cfg->line_out_type != AUTO_PIN_HP_OUT)
		spec->स्थिर_channel_count = max(spec->स्थिर_channel_count,
						cfg->hp_outs * 2);
	spec->multiout.max_channels = max(spec->ext_channel_count,
					  spec->स्थिर_channel_count);

	err = check_स्वतः_mute_availability(codec);
	अगर (err < 0)
		वापस err;

	err = check_dyn_adc_चयन(codec);
	अगर (err < 0)
		वापस err;

	err = check_स्वतः_mic_availability(codec);
	अगर (err < 0)
		वापस err;

	/* add stereo mix अगर available and not enabled yet */
	अगर (!spec->स्वतः_mic && spec->mixer_nid &&
	    spec->add_stereo_mix_input == HDA_HINT_STEREO_MIX_AUTO &&
	    spec->input_mux.num_items > 1) अणु
		err = parse_capture_source(codec, spec->mixer_nid,
					   CFG_IDX_MIX, spec->num_all_adcs,
					   "Stereo Mix", 0);
		अगर (err < 0)
			वापस err;
	पूर्ण


	err = create_capture_mixers(codec);
	अगर (err < 0)
		वापस err;

	err = parse_mic_boost(codec);
	अगर (err < 0)
		वापस err;

	/* create "Headphone Mic Jack Mode" अगर no input selection is
	 * available (or user specअगरies add_jack_modes hपूर्णांक)
	 */
	अगर (spec->hp_mic_pin &&
	    (spec->स्वतः_mic || spec->input_mux.num_items == 1 ||
	     spec->add_jack_modes)) अणु
		err = create_hp_mic_jack_mode(codec, spec->hp_mic_pin);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (spec->add_jack_modes) अणु
		अगर (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT) अणु
			err = create_out_jack_modes(codec, cfg->line_outs,
						    cfg->line_out_pins);
			अगर (err < 0)
				वापस err;
		पूर्ण
		अगर (cfg->line_out_type != AUTO_PIN_HP_OUT) अणु
			err = create_out_jack_modes(codec, cfg->hp_outs,
						    cfg->hp_pins);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	/* add घातer-up pin callbacks at last */
	add_all_pin_घातer_ctls(codec, true);

	/* mute all aamix input initially */
	अगर (spec->mixer_nid)
		mute_all_mixer_nid(codec, spec->mixer_nid);

 dig_only:
	parse_digital(codec);

	अगर (spec->घातer_करोwn_unused || codec->घातer_save_node) अणु
		अगर (!codec->घातer_filter)
			codec->घातer_filter = snd_hda_gen_path_घातer_filter;
		अगर (!codec->patch_ops.stream_pm)
			codec->patch_ops.stream_pm = snd_hda_gen_stream_pm;
	पूर्ण

	अगर (!spec->no_analog && spec->beep_nid) अणु
		err = snd_hda_attach_beep_device(codec, spec->beep_nid);
		अगर (err < 0)
			वापस err;
		अगर (codec->beep && codec->घातer_save_node) अणु
			err = add_fake_beep_paths(codec);
			अगर (err < 0)
				वापस err;
			codec->beep->घातer_hook = beep_घातer_hook;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_parse_स्वतः_config);


/*
 * Build control elements
 */

/* follower controls क्रम भव master */
अटल स्थिर अक्षर * स्थिर follower_pfxs[] = अणु
	"Front", "Surround", "Center", "LFE", "Side",
	"Headphone", "Speaker", "Mono", "Line Out",
	"CLFE", "Bass Speaker", "PCM",
	"Speaker Front", "Speaker Surround", "Speaker CLFE", "Speaker Side",
	"Headphone Front", "Headphone Surround", "Headphone CLFE",
	"Headphone Side", "Headphone+LO", "Speaker+LO",
	शून्य,
पूर्ण;

/**
 * snd_hda_gen_build_controls - Build controls from the parsed results
 * @codec: the HDA codec
 *
 * Pass this to build_controls patch_ops.
 */
पूर्णांक snd_hda_gen_build_controls(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक err;

	अगर (spec->kctls.used) अणु
		err = snd_hda_add_new_ctls(codec, spec->kctls.list);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (spec->multiout.dig_out_nid) अणु
		err = snd_hda_create_dig_out_ctls(codec,
						  spec->multiout.dig_out_nid,
						  spec->multiout.dig_out_nid,
						  spec->pcm_rec[1]->pcm_type);
		अगर (err < 0)
			वापस err;
		अगर (!spec->no_analog) अणु
			err = snd_hda_create_spdअगर_share_sw(codec,
							    &spec->multiout);
			अगर (err < 0)
				वापस err;
			spec->multiout.share_spdअगर = 1;
		पूर्ण
	पूर्ण
	अगर (spec->dig_in_nid) अणु
		err = snd_hda_create_spdअगर_in_ctls(codec, spec->dig_in_nid);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* अगर we have no master control, let's create it */
	अगर (!spec->no_analog && !spec->suppress_vmaster &&
	    !snd_hda_find_mixer_ctl(codec, "Master Playback Volume")) अणु
		err = snd_hda_add_vmaster(codec, "Master Playback Volume",
					  spec->vmaster_tlv, follower_pfxs,
					  "Playback Volume", 0);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (!spec->no_analog && !spec->suppress_vmaster &&
	    !snd_hda_find_mixer_ctl(codec, "Master Playback Switch")) अणु
		err = __snd_hda_add_vmaster(codec, "Master Playback Switch",
					    शून्य, follower_pfxs,
					    "Playback Switch", true,
					    spec->vmaster_mute_led ?
						SNDRV_CTL_ELEM_ACCESS_SPK_LED : 0,
					    &spec->vmaster_mute.sw_kctl);
		अगर (err < 0)
			वापस err;
		अगर (spec->vmaster_mute.hook) अणु
			snd_hda_add_vmaster_hook(codec, &spec->vmaster_mute);
			snd_hda_sync_vmaster_hook(&spec->vmaster_mute);
		पूर्ण
	पूर्ण

	मुक्त_kctls(spec); /* no दीर्घer needed */

	err = snd_hda_jack_add_kctls(codec, &spec->स्वतःcfg);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_build_controls);


/*
 * PCM definitions
 */

अटल व्योम call_pcm_playback_hook(काष्ठा hda_pcm_stream *hinfo,
				   काष्ठा hda_codec *codec,
				   काष्ठा snd_pcm_substream *substream,
				   पूर्णांक action)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	अगर (spec->pcm_playback_hook)
		spec->pcm_playback_hook(hinfo, codec, substream, action);
पूर्ण

अटल व्योम call_pcm_capture_hook(काष्ठा hda_pcm_stream *hinfo,
				  काष्ठा hda_codec *codec,
				  काष्ठा snd_pcm_substream *substream,
				  पूर्णांक action)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	अगर (spec->pcm_capture_hook)
		spec->pcm_capture_hook(hinfo, codec, substream, action);
पूर्ण

/*
 * Analog playback callbacks
 */
अटल पूर्णांक playback_pcm_खोलो(काष्ठा hda_pcm_stream *hinfo,
			     काष्ठा hda_codec *codec,
			     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक err;

	mutex_lock(&spec->pcm_mutex);
	err = snd_hda_multi_out_analog_खोलो(codec,
					    &spec->multiout, substream,
					     hinfo);
	अगर (!err) अणु
		spec->active_streams |= 1 << STREAM_MULTI_OUT;
		call_pcm_playback_hook(hinfo, codec, substream,
				       HDA_GEN_PCM_ACT_OPEN);
	पूर्ण
	mutex_unlock(&spec->pcm_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक playback_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
				काष्ठा hda_codec *codec,
				अचिन्हित पूर्णांक stream_tag,
				अचिन्हित पूर्णांक क्रमmat,
				काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक err;

	err = snd_hda_multi_out_analog_prepare(codec, &spec->multiout,
					       stream_tag, क्रमmat, substream);
	अगर (!err)
		call_pcm_playback_hook(hinfo, codec, substream,
				       HDA_GEN_PCM_ACT_PREPARE);
	वापस err;
पूर्ण

अटल पूर्णांक playback_pcm_cleanup(काष्ठा hda_pcm_stream *hinfo,
				काष्ठा hda_codec *codec,
				काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक err;

	err = snd_hda_multi_out_analog_cleanup(codec, &spec->multiout);
	अगर (!err)
		call_pcm_playback_hook(hinfo, codec, substream,
				       HDA_GEN_PCM_ACT_CLEANUP);
	वापस err;
पूर्ण

अटल पूर्णांक playback_pcm_बंद(काष्ठा hda_pcm_stream *hinfo,
			      काष्ठा hda_codec *codec,
			      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	mutex_lock(&spec->pcm_mutex);
	spec->active_streams &= ~(1 << STREAM_MULTI_OUT);
	call_pcm_playback_hook(hinfo, codec, substream,
			       HDA_GEN_PCM_ACT_CLOSE);
	mutex_unlock(&spec->pcm_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक capture_pcm_खोलो(काष्ठा hda_pcm_stream *hinfo,
			    काष्ठा hda_codec *codec,
			    काष्ठा snd_pcm_substream *substream)
अणु
	call_pcm_capture_hook(hinfo, codec, substream, HDA_GEN_PCM_ACT_OPEN);
	वापस 0;
पूर्ण

अटल पूर्णांक capture_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
			       काष्ठा hda_codec *codec,
			       अचिन्हित पूर्णांक stream_tag,
			       अचिन्हित पूर्णांक क्रमmat,
			       काष्ठा snd_pcm_substream *substream)
अणु
	snd_hda_codec_setup_stream(codec, hinfo->nid, stream_tag, 0, क्रमmat);
	call_pcm_capture_hook(hinfo, codec, substream,
			      HDA_GEN_PCM_ACT_PREPARE);
	वापस 0;
पूर्ण

अटल पूर्णांक capture_pcm_cleanup(काष्ठा hda_pcm_stream *hinfo,
			       काष्ठा hda_codec *codec,
			       काष्ठा snd_pcm_substream *substream)
अणु
	snd_hda_codec_cleanup_stream(codec, hinfo->nid);
	call_pcm_capture_hook(hinfo, codec, substream,
			      HDA_GEN_PCM_ACT_CLEANUP);
	वापस 0;
पूर्ण

अटल पूर्णांक capture_pcm_बंद(काष्ठा hda_pcm_stream *hinfo,
			     काष्ठा hda_codec *codec,
			     काष्ठा snd_pcm_substream *substream)
अणु
	call_pcm_capture_hook(hinfo, codec, substream, HDA_GEN_PCM_ACT_CLOSE);
	वापस 0;
पूर्ण

अटल पूर्णांक alt_playback_pcm_खोलो(काष्ठा hda_pcm_stream *hinfo,
				 काष्ठा hda_codec *codec,
				 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक err = 0;

	mutex_lock(&spec->pcm_mutex);
	अगर (spec->indep_hp && !spec->indep_hp_enabled)
		err = -EBUSY;
	अन्यथा
		spec->active_streams |= 1 << STREAM_INDEP_HP;
	call_pcm_playback_hook(hinfo, codec, substream,
			       HDA_GEN_PCM_ACT_OPEN);
	mutex_unlock(&spec->pcm_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक alt_playback_pcm_बंद(काष्ठा hda_pcm_stream *hinfo,
				  काष्ठा hda_codec *codec,
				  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	mutex_lock(&spec->pcm_mutex);
	spec->active_streams &= ~(1 << STREAM_INDEP_HP);
	call_pcm_playback_hook(hinfo, codec, substream,
			       HDA_GEN_PCM_ACT_CLOSE);
	mutex_unlock(&spec->pcm_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक alt_playback_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
				    काष्ठा hda_codec *codec,
				    अचिन्हित पूर्णांक stream_tag,
				    अचिन्हित पूर्णांक क्रमmat,
				    काष्ठा snd_pcm_substream *substream)
अणु
	snd_hda_codec_setup_stream(codec, hinfo->nid, stream_tag, 0, क्रमmat);
	call_pcm_playback_hook(hinfo, codec, substream,
			       HDA_GEN_PCM_ACT_PREPARE);
	वापस 0;
पूर्ण

अटल पूर्णांक alt_playback_pcm_cleanup(काष्ठा hda_pcm_stream *hinfo,
				    काष्ठा hda_codec *codec,
				    काष्ठा snd_pcm_substream *substream)
अणु
	snd_hda_codec_cleanup_stream(codec, hinfo->nid);
	call_pcm_playback_hook(hinfo, codec, substream,
			       HDA_GEN_PCM_ACT_CLEANUP);
	वापस 0;
पूर्ण

/*
 * Digital out
 */
अटल पूर्णांक dig_playback_pcm_खोलो(काष्ठा hda_pcm_stream *hinfo,
				 काष्ठा hda_codec *codec,
				 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	वापस snd_hda_multi_out_dig_खोलो(codec, &spec->multiout);
पूर्ण

अटल पूर्णांक dig_playback_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
				    काष्ठा hda_codec *codec,
				    अचिन्हित पूर्णांक stream_tag,
				    अचिन्हित पूर्णांक क्रमmat,
				    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	वापस snd_hda_multi_out_dig_prepare(codec, &spec->multiout,
					     stream_tag, क्रमmat, substream);
पूर्ण

अटल पूर्णांक dig_playback_pcm_cleanup(काष्ठा hda_pcm_stream *hinfo,
				    काष्ठा hda_codec *codec,
				    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	वापस snd_hda_multi_out_dig_cleanup(codec, &spec->multiout);
पूर्ण

अटल पूर्णांक dig_playback_pcm_बंद(काष्ठा hda_pcm_stream *hinfo,
				  काष्ठा hda_codec *codec,
				  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	वापस snd_hda_multi_out_dig_बंद(codec, &spec->multiout);
पूर्ण

/*
 * Analog capture
 */
#घोषणा alt_capture_pcm_खोलो	capture_pcm_खोलो
#घोषणा alt_capture_pcm_बंद	capture_pcm_बंद

अटल पूर्णांक alt_capture_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
				   काष्ठा hda_codec *codec,
				   अचिन्हित पूर्णांक stream_tag,
				   अचिन्हित पूर्णांक क्रमmat,
				   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;

	snd_hda_codec_setup_stream(codec, spec->adc_nids[substream->number + 1],
				   stream_tag, 0, क्रमmat);
	call_pcm_capture_hook(hinfo, codec, substream,
			      HDA_GEN_PCM_ACT_PREPARE);
	वापस 0;
पूर्ण

अटल पूर्णांक alt_capture_pcm_cleanup(काष्ठा hda_pcm_stream *hinfo,
				   काष्ठा hda_codec *codec,
				   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;

	snd_hda_codec_cleanup_stream(codec,
				     spec->adc_nids[substream->number + 1]);
	call_pcm_capture_hook(hinfo, codec, substream,
			      HDA_GEN_PCM_ACT_CLEANUP);
	वापस 0;
पूर्ण

/*
 */
अटल स्थिर काष्ठा hda_pcm_stream pcm_analog_playback = अणु
	.substreams = 1,
	.channels_min = 2,
	.channels_max = 8,
	/* NID is set in build_pcms */
	.ops = अणु
		.खोलो = playback_pcm_खोलो,
		.बंद = playback_pcm_बंद,
		.prepare = playback_pcm_prepare,
		.cleanup = playback_pcm_cleanup
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_pcm_stream pcm_analog_capture = अणु
	.substreams = 1,
	.channels_min = 2,
	.channels_max = 2,
	/* NID is set in build_pcms */
	.ops = अणु
		.खोलो = capture_pcm_खोलो,
		.बंद = capture_pcm_बंद,
		.prepare = capture_pcm_prepare,
		.cleanup = capture_pcm_cleanup
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_pcm_stream pcm_analog_alt_playback = अणु
	.substreams = 1,
	.channels_min = 2,
	.channels_max = 2,
	/* NID is set in build_pcms */
	.ops = अणु
		.खोलो = alt_playback_pcm_खोलो,
		.बंद = alt_playback_pcm_बंद,
		.prepare = alt_playback_pcm_prepare,
		.cleanup = alt_playback_pcm_cleanup
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_pcm_stream pcm_analog_alt_capture = अणु
	.substreams = 2, /* can be overridden */
	.channels_min = 2,
	.channels_max = 2,
	/* NID is set in build_pcms */
	.ops = अणु
		.खोलो = alt_capture_pcm_खोलो,
		.बंद = alt_capture_pcm_बंद,
		.prepare = alt_capture_pcm_prepare,
		.cleanup = alt_capture_pcm_cleanup
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_pcm_stream pcm_digital_playback = अणु
	.substreams = 1,
	.channels_min = 2,
	.channels_max = 2,
	/* NID is set in build_pcms */
	.ops = अणु
		.खोलो = dig_playback_pcm_खोलो,
		.बंद = dig_playback_pcm_बंद,
		.prepare = dig_playback_pcm_prepare,
		.cleanup = dig_playback_pcm_cleanup
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_pcm_stream pcm_digital_capture = अणु
	.substreams = 1,
	.channels_min = 2,
	.channels_max = 2,
	/* NID is set in build_pcms */
पूर्ण;

/* Used by build_pcms to flag that a PCM has no playback stream */
अटल स्थिर काष्ठा hda_pcm_stream pcm_null_stream = अणु
	.substreams = 0,
	.channels_min = 0,
	.channels_max = 0,
पूर्ण;

/*
 * dynamic changing ADC PCM streams
 */
अटल bool dyn_adc_pcm_resetup(काष्ठा hda_codec *codec, पूर्णांक cur)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	hda_nid_t new_adc = spec->adc_nids[spec->dyn_adc_idx[cur]];

	अगर (spec->cur_adc && spec->cur_adc != new_adc) अणु
		/* stream is running, let's swap the current ADC */
		__snd_hda_codec_cleanup_stream(codec, spec->cur_adc, 1);
		spec->cur_adc = new_adc;
		snd_hda_codec_setup_stream(codec, new_adc,
					   spec->cur_adc_stream_tag, 0,
					   spec->cur_adc_क्रमmat);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* analog capture with dynamic dual-adc changes */
अटल पूर्णांक dyn_adc_capture_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
				       काष्ठा hda_codec *codec,
				       अचिन्हित पूर्णांक stream_tag,
				       अचिन्हित पूर्णांक क्रमmat,
				       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	spec->cur_adc = spec->adc_nids[spec->dyn_adc_idx[spec->cur_mux[0]]];
	spec->cur_adc_stream_tag = stream_tag;
	spec->cur_adc_क्रमmat = क्रमmat;
	snd_hda_codec_setup_stream(codec, spec->cur_adc, stream_tag, 0, क्रमmat);
	call_pcm_capture_hook(hinfo, codec, substream, HDA_GEN_PCM_ACT_PREPARE);
	वापस 0;
पूर्ण

अटल पूर्णांक dyn_adc_capture_pcm_cleanup(काष्ठा hda_pcm_stream *hinfo,
				       काष्ठा hda_codec *codec,
				       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	snd_hda_codec_cleanup_stream(codec, spec->cur_adc);
	spec->cur_adc = 0;
	call_pcm_capture_hook(hinfo, codec, substream, HDA_GEN_PCM_ACT_CLEANUP);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hda_pcm_stream dyn_adc_pcm_analog_capture = अणु
	.substreams = 1,
	.channels_min = 2,
	.channels_max = 2,
	.nid = 0, /* fill later */
	.ops = अणु
		.prepare = dyn_adc_capture_pcm_prepare,
		.cleanup = dyn_adc_capture_pcm_cleanup
	पूर्ण,
पूर्ण;

अटल व्योम fill_pcm_stream_name(अक्षर *str, माप_प्रकार len, स्थिर अक्षर *sfx,
				 स्थिर अक्षर *chip_name)
अणु
	अक्षर *p;

	अगर (*str)
		वापस;
	strscpy(str, chip_name, len);

	/* drop non-alnum अक्षरs after a space */
	क्रम (p = म_अक्षर(str, ' '); p; p = strchr(p + 1, ' ')) अणु
		अगर (!है_अक्षर_अंक(p[1])) अणु
			*p = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	strlcat(str, sfx, len);
पूर्ण

/* copy PCM stream info from @शेष_str, and override non-शून्य entries
 * from @spec_str and @nid
 */
अटल व्योम setup_pcm_stream(काष्ठा hda_pcm_stream *str,
			     स्थिर काष्ठा hda_pcm_stream *शेष_str,
			     स्थिर काष्ठा hda_pcm_stream *spec_str,
			     hda_nid_t nid)
अणु
	*str = *शेष_str;
	अगर (nid)
		str->nid = nid;
	अगर (spec_str) अणु
		अगर (spec_str->substreams)
			str->substreams = spec_str->substreams;
		अगर (spec_str->channels_min)
			str->channels_min = spec_str->channels_min;
		अगर (spec_str->channels_max)
			str->channels_max = spec_str->channels_max;
		अगर (spec_str->rates)
			str->rates = spec_str->rates;
		अगर (spec_str->क्रमmats)
			str->क्रमmats = spec_str->क्रमmats;
		अगर (spec_str->maxbps)
			str->maxbps = spec_str->maxbps;
	पूर्ण
पूर्ण

/**
 * snd_hda_gen_build_pcms - build PCM streams based on the parsed results
 * @codec: the HDA codec
 *
 * Pass this to build_pcms patch_ops.
 */
पूर्णांक snd_hda_gen_build_pcms(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा hda_pcm *info;
	bool have_multi_adcs;

	अगर (spec->no_analog)
		जाओ skip_analog;

	fill_pcm_stream_name(spec->stream_name_analog,
			     माप(spec->stream_name_analog),
			     " Analog", codec->core.chip_name);
	info = snd_hda_codec_pcm_new(codec, "%s", spec->stream_name_analog);
	अगर (!info)
		वापस -ENOMEM;
	spec->pcm_rec[0] = info;

	अगर (spec->multiout.num_dacs > 0) अणु
		setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_PLAYBACK],
				 &pcm_analog_playback,
				 spec->stream_analog_playback,
				 spec->multiout.dac_nids[0]);
		info->stream[SNDRV_PCM_STREAM_PLAYBACK].channels_max =
			spec->multiout.max_channels;
		अगर (spec->स्वतःcfg.line_out_type == AUTO_PIN_SPEAKER_OUT &&
		    spec->स्वतःcfg.line_outs == 2)
			info->stream[SNDRV_PCM_STREAM_PLAYBACK].chmap =
				snd_pcm_2_1_chmaps;
	पूर्ण
	अगर (spec->num_adc_nids) अणु
		setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_CAPTURE],
				 (spec->dyn_adc_चयन ?
				  &dyn_adc_pcm_analog_capture : &pcm_analog_capture),
				 spec->stream_analog_capture,
				 spec->adc_nids[0]);
	पूर्ण

 skip_analog:
	/* SPDIF क्रम stream index #1 */
	अगर (spec->multiout.dig_out_nid || spec->dig_in_nid) अणु
		fill_pcm_stream_name(spec->stream_name_digital,
				     माप(spec->stream_name_digital),
				     " Digital", codec->core.chip_name);
		info = snd_hda_codec_pcm_new(codec, "%s",
					     spec->stream_name_digital);
		अगर (!info)
			वापस -ENOMEM;
		codec->follower_dig_outs = spec->multiout.follower_dig_outs;
		spec->pcm_rec[1] = info;
		अगर (spec->dig_out_type)
			info->pcm_type = spec->dig_out_type;
		अन्यथा
			info->pcm_type = HDA_PCM_TYPE_SPDIF;
		अगर (spec->multiout.dig_out_nid)
			setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_PLAYBACK],
					 &pcm_digital_playback,
					 spec->stream_digital_playback,
					 spec->multiout.dig_out_nid);
		अगर (spec->dig_in_nid)
			setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_CAPTURE],
					 &pcm_digital_capture,
					 spec->stream_digital_capture,
					 spec->dig_in_nid);
	पूर्ण

	अगर (spec->no_analog)
		वापस 0;

	/* If the use of more than one ADC is requested क्रम the current
	 * model, configure a second analog capture-only PCM.
	 */
	have_multi_adcs = (spec->num_adc_nids > 1) &&
		!spec->dyn_adc_चयन && !spec->स्वतः_mic;
	/* Additional Analaog capture क्रम index #2 */
	अगर (spec->alt_dac_nid || have_multi_adcs) अणु
		fill_pcm_stream_name(spec->stream_name_alt_analog,
				     माप(spec->stream_name_alt_analog),
			     " Alt Analog", codec->core.chip_name);
		info = snd_hda_codec_pcm_new(codec, "%s",
					     spec->stream_name_alt_analog);
		अगर (!info)
			वापस -ENOMEM;
		spec->pcm_rec[2] = info;
		अगर (spec->alt_dac_nid)
			setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_PLAYBACK],
					 &pcm_analog_alt_playback,
					 spec->stream_analog_alt_playback,
					 spec->alt_dac_nid);
		अन्यथा
			setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_PLAYBACK],
					 &pcm_null_stream, शून्य, 0);
		अगर (have_multi_adcs) अणु
			setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_CAPTURE],
					 &pcm_analog_alt_capture,
					 spec->stream_analog_alt_capture,
					 spec->adc_nids[1]);
			info->stream[SNDRV_PCM_STREAM_CAPTURE].substreams =
				spec->num_adc_nids - 1;
		पूर्ण अन्यथा अणु
			setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_CAPTURE],
					 &pcm_null_stream, शून्य, 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_build_pcms);


/*
 * Standard स्वतः-parser initializations
 */

/* configure the given path as a proper output */
अटल व्योम set_output_and_unmute(काष्ठा hda_codec *codec, पूर्णांक path_idx)
अणु
	काष्ठा nid_path *path;
	hda_nid_t pin;

	path = snd_hda_get_path_from_idx(codec, path_idx);
	अगर (!path || !path->depth)
		वापस;
	pin = path->path[path->depth - 1];
	restore_pin_ctl(codec, pin);
	snd_hda_activate_path(codec, path, path->active,
			      aamix_शेष(codec->spec));
	set_pin_eapd(codec, pin, path->active);
पूर्ण

/* initialize primary output paths */
अटल व्योम init_multi_out(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i;

	क्रम (i = 0; i < spec->स्वतःcfg.line_outs; i++)
		set_output_and_unmute(codec, spec->out_paths[i]);
पूर्ण


अटल व्योम __init_extra_out(काष्ठा hda_codec *codec, पूर्णांक num_outs, पूर्णांक *paths)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_outs; i++)
		set_output_and_unmute(codec, paths[i]);
पूर्ण

/* initialize hp and speaker paths */
अटल व्योम init_extra_out(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;

	अगर (spec->स्वतःcfg.line_out_type != AUTO_PIN_HP_OUT)
		__init_extra_out(codec, spec->स्वतःcfg.hp_outs, spec->hp_paths);
	अगर (spec->स्वतःcfg.line_out_type != AUTO_PIN_SPEAKER_OUT)
		__init_extra_out(codec, spec->स्वतःcfg.speaker_outs,
				 spec->speaker_paths);
पूर्ण

/* initialize multi-io paths */
अटल व्योम init_multi_io(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i;

	क्रम (i = 0; i < spec->multi_ios; i++) अणु
		hda_nid_t pin = spec->multi_io[i].pin;
		काष्ठा nid_path *path;
		path = get_multiio_path(codec, i);
		अगर (!path)
			जारी;
		अगर (!spec->multi_io[i].ctl_in)
			spec->multi_io[i].ctl_in =
				snd_hda_codec_get_pin_target(codec, pin);
		snd_hda_activate_path(codec, path, path->active,
				      aamix_शेष(spec));
	पूर्ण
पूर्ण

अटल व्योम init_aamix_paths(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;

	अगर (!spec->have_aamix_ctl)
		वापस;
	अगर (!has_aamix_out_paths(spec))
		वापस;
	update_aamix_paths(codec, spec->aamix_mode, spec->out_paths[0],
			   spec->aamix_out_paths[0],
			   spec->स्वतःcfg.line_out_type);
	update_aamix_paths(codec, spec->aamix_mode, spec->hp_paths[0],
			   spec->aamix_out_paths[1],
			   AUTO_PIN_HP_OUT);
	update_aamix_paths(codec, spec->aamix_mode, spec->speaker_paths[0],
			   spec->aamix_out_paths[2],
			   AUTO_PIN_SPEAKER_OUT);
पूर्ण

/* set up input pins and loopback paths */
अटल व्योम init_analog_input(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	पूर्णांक i;

	क्रम (i = 0; i < cfg->num_inमाला_दो; i++) अणु
		hda_nid_t nid = cfg->inमाला_दो[i].pin;
		अगर (is_input_pin(codec, nid))
			restore_pin_ctl(codec, nid);

		/* init loopback inमाला_दो */
		अगर (spec->mixer_nid) अणु
			resume_path_from_idx(codec, spec->loopback_paths[i]);
			resume_path_from_idx(codec, spec->loopback_merge_path);
		पूर्ण
	पूर्ण
पूर्ण

/* initialize ADC paths */
अटल व्योम init_input_src(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	काष्ठा hda_input_mux *imux = &spec->input_mux;
	काष्ठा nid_path *path;
	पूर्णांक i, c, nums;

	अगर (spec->dyn_adc_चयन)
		nums = 1;
	अन्यथा
		nums = spec->num_adc_nids;

	क्रम (c = 0; c < nums; c++) अणु
		क्रम (i = 0; i < imux->num_items; i++) अणु
			path = get_input_path(codec, c, i);
			अगर (path) अणु
				bool active = path->active;
				अगर (i == spec->cur_mux[c])
					active = true;
				snd_hda_activate_path(codec, path, active, false);
			पूर्ण
		पूर्ण
		अगर (spec->hp_mic)
			update_hp_mic(codec, c, true);
	पूर्ण

	अगर (spec->cap_sync_hook)
		spec->cap_sync_hook(codec, शून्य, शून्य);
पूर्ण

/* set right pin controls क्रम digital I/O */
अटल व्योम init_digital(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक i;
	hda_nid_t pin;

	क्रम (i = 0; i < spec->स्वतःcfg.dig_outs; i++)
		set_output_and_unmute(codec, spec->digout_paths[i]);
	pin = spec->स्वतःcfg.dig_in_pin;
	अगर (pin) अणु
		restore_pin_ctl(codec, pin);
		resume_path_from_idx(codec, spec->digin_path);
	पूर्ण
पूर्ण

/* clear unsol-event tags on unused pins; Conexant codecs seem to leave
 * invalid unsol tags by some reason
 */
अटल व्योम clear_unsol_on_unused_pins(काष्ठा hda_codec *codec)
अणु
	स्थिर काष्ठा hda_pincfg *pin;
	पूर्णांक i;

	snd_array_क्रम_each(&codec->init_pins, i, pin) अणु
		hda_nid_t nid = pin->nid;
		अगर (is_jack_detectable(codec, nid) &&
		    !snd_hda_jack_tbl_get(codec, nid))
			snd_hda_codec_ग_लिखो_cache(codec, nid, 0,
					AC_VERB_SET_UNSOLICITED_ENABLE, 0);
	पूर्ण
पूर्ण

/**
 * snd_hda_gen_init - initialize the generic spec
 * @codec: the HDA codec
 *
 * This can be put as patch_ops init function.
 */
पूर्णांक snd_hda_gen_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;

	अगर (spec->init_hook)
		spec->init_hook(codec);

	अगर (!spec->skip_verbs)
		snd_hda_apply_verbs(codec);

	init_multi_out(codec);
	init_extra_out(codec);
	init_multi_io(codec);
	init_aamix_paths(codec);
	init_analog_input(codec);
	init_input_src(codec);
	init_digital(codec);

	clear_unsol_on_unused_pins(codec);

	sync_all_pin_घातer_ctls(codec);

	/* call init functions of standard स्वतः-mute helpers */
	update_स्वतःmute_all(codec);

	snd_hda_regmap_sync(codec);

	अगर (spec->vmaster_mute.sw_kctl && spec->vmaster_mute.hook)
		snd_hda_sync_vmaster_hook(&spec->vmaster_mute);

	hda_call_check_घातer_status(codec, 0x01);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_init);

/**
 * snd_hda_gen_मुक्त - मुक्त the generic spec
 * @codec: the HDA codec
 *
 * This can be put as patch_ops मुक्त function.
 */
व्योम snd_hda_gen_मुक्त(काष्ठा hda_codec *codec)
अणु
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_FREE);
	snd_hda_gen_spec_मुक्त(codec->spec);
	kमुक्त(codec->spec);
	codec->spec = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_मुक्त);

/**
 * snd_hda_gen_reboot_notअगरy - Make codec enter D3 beक्रमe rebooting
 * @codec: the HDA codec
 *
 * This can be put as patch_ops reboot_notअगरy function.
 */
व्योम snd_hda_gen_reboot_notअगरy(काष्ठा hda_codec *codec)
अणु
	/* Make the codec enter D3 to aव्योम spurious noises from the पूर्णांकernal
	 * speaker during (and after) reboot
	 */
	snd_hda_codec_set_घातer_to_all(codec, codec->core.afg, AC_PWRST_D3);
	snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0,
			    AC_VERB_SET_POWER_STATE, AC_PWRST_D3);
	msleep(10);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_reboot_notअगरy);

#अगर_घोषित CONFIG_PM
/**
 * snd_hda_gen_check_घातer_status - check the loopback घातer save state
 * @codec: the HDA codec
 * @nid: NID to inspect
 *
 * This can be put as patch_ops check_घातer_status function.
 */
पूर्णांक snd_hda_gen_check_घातer_status(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	वापस snd_hda_check_amp_list_घातer(codec, &spec->loopback, nid);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_gen_check_घातer_status);
#पूर्ण_अगर


/*
 * the generic codec support
 */

अटल स्थिर काष्ठा hda_codec_ops generic_patch_ops = अणु
	.build_controls = snd_hda_gen_build_controls,
	.build_pcms = snd_hda_gen_build_pcms,
	.init = snd_hda_gen_init,
	.मुक्त = snd_hda_gen_मुक्त,
	.unsol_event = snd_hda_jack_unsol_event,
	.reboot_notअगरy = snd_hda_gen_reboot_notअगरy,
#अगर_घोषित CONFIG_PM
	.check_घातer_status = snd_hda_gen_check_घातer_status,
#पूर्ण_अगर
पूर्ण;

/*
 * snd_hda_parse_generic_codec - Generic codec parser
 * @codec: the HDA codec
 */
अटल पूर्णांक snd_hda_parse_generic_codec(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec;
	पूर्णांक err;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	snd_hda_gen_spec_init(spec);
	codec->spec = spec;

	err = snd_hda_parse_pin_defcfg(codec, &spec->स्वतःcfg, शून्य, 0);
	अगर (err < 0)
		जाओ error;

	err = snd_hda_gen_parse_स्वतः_config(codec, &spec->स्वतःcfg);
	अगर (err < 0)
		जाओ error;

	codec->patch_ops = generic_patch_ops;
	वापस 0;

error:
	snd_hda_gen_मुक्त(codec);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा hda_device_id snd_hda_id_generic[] = अणु
	HDA_CODEC_ENTRY(HDA_CODEC_ID_GENERIC, "Generic", snd_hda_parse_generic_codec),
	अणुपूर्ण /* terminator */
पूर्ण;
MODULE_DEVICE_TABLE(hdaudio, snd_hda_id_generic);

अटल काष्ठा hda_codec_driver generic_driver = अणु
	.id = snd_hda_id_generic,
पूर्ण;

module_hda_codec_driver(generic_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Generic HD-audio codec parser");
