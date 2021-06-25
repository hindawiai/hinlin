<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Virtual master and follower controls
 *
 *  Copyright (c) 2008 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>

/*
 * a subset of inक्रमmation वापसed via ctl info callback
 */
काष्ठा link_ctl_info अणु
	snd_ctl_elem_type_t type; /* value type */
	पूर्णांक count;		/* item count */
	पूर्णांक min_val, max_val;	/* min, max values */
पूर्ण;

/*
 * link master - this contains a list of follower controls that are
 * identical types, i.e. info वापसs the same value type and value
 * ranges, but may have dअगरferent number of counts.
 *
 * The master control is so far only mono volume/चयन क्रम simplicity.
 * The same value will be applied to all followers.
 */
काष्ठा link_master अणु
	काष्ठा list_head followers;
	काष्ठा link_ctl_info info;
	पूर्णांक val;		/* the master value */
	अचिन्हित पूर्णांक tlv[4];
	व्योम (*hook)(व्योम *निजी_data, पूर्णांक);
	व्योम *hook_निजी_data;
पूर्ण;

/*
 * link follower - this contains a follower control element
 *
 * It fakes the control callbacks with additional attenuation by the
 * master control.  A follower may have either one or two channels.
 */

काष्ठा link_follower अणु
	काष्ठा list_head list;
	काष्ठा link_master *master;
	काष्ठा link_ctl_info info;
	पूर्णांक vals[2];		/* current values */
	अचिन्हित पूर्णांक flags;
	काष्ठा snd_kcontrol *kctl; /* original kcontrol poपूर्णांकer */
	काष्ठा snd_kcontrol follower; /* the copy of original control entry */
पूर्ण;

अटल पूर्णांक follower_update(काष्ठा link_follower *follower)
अणु
	काष्ठा snd_ctl_elem_value *uctl;
	पूर्णांक err, ch;

	uctl = kzalloc(माप(*uctl), GFP_KERNEL);
	अगर (!uctl)
		वापस -ENOMEM;
	uctl->id = follower->follower.id;
	err = follower->follower.get(&follower->follower, uctl);
	अगर (err < 0)
		जाओ error;
	क्रम (ch = 0; ch < follower->info.count; ch++)
		follower->vals[ch] = uctl->value.पूर्णांकeger.value[ch];
 error:
	kमुक्त(uctl);
	वापस err < 0 ? err : 0;
पूर्ण

/* get the follower ctl info and save the initial values */
अटल पूर्णांक follower_init(काष्ठा link_follower *follower)
अणु
	काष्ठा snd_ctl_elem_info *uinfo;
	पूर्णांक err;

	अगर (follower->info.count) अणु
		/* alपढ़ोy initialized */
		अगर (follower->flags & SND_CTL_FOLLOWER_NEED_UPDATE)
			वापस follower_update(follower);
		वापस 0;
	पूर्ण

	uinfo = kदो_स्मृति(माप(*uinfo), GFP_KERNEL);
	अगर (!uinfo)
		वापस -ENOMEM;
	uinfo->id = follower->follower.id;
	err = follower->follower.info(&follower->follower, uinfo);
	अगर (err < 0) अणु
		kमुक्त(uinfo);
		वापस err;
	पूर्ण
	follower->info.type = uinfo->type;
	follower->info.count = uinfo->count;
	अगर (follower->info.count > 2  ||
	    (follower->info.type != SNDRV_CTL_ELEM_TYPE_INTEGER &&
	     follower->info.type != SNDRV_CTL_ELEM_TYPE_BOOLEAN)) अणु
		pr_err("ALSA: vmaster: invalid follower element\n");
		kमुक्त(uinfo);
		वापस -EINVAL;
	पूर्ण
	follower->info.min_val = uinfo->value.पूर्णांकeger.min;
	follower->info.max_val = uinfo->value.पूर्णांकeger.max;
	kमुक्त(uinfo);

	वापस follower_update(follower);
पूर्ण

/* initialize master volume */
अटल पूर्णांक master_init(काष्ठा link_master *master)
अणु
	काष्ठा link_follower *follower;

	अगर (master->info.count)
		वापस 0; /* alपढ़ोy initialized */

	list_क्रम_each_entry(follower, &master->followers, list) अणु
		पूर्णांक err = follower_init(follower);
		अगर (err < 0)
			वापस err;
		master->info = follower->info;
		master->info.count = 1; /* always mono */
		/* set full volume as शेष (= no attenuation) */
		master->val = master->info.max_val;
		अगर (master->hook)
			master->hook(master->hook_निजी_data, master->val);
		वापस 1;
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक follower_get_val(काष्ठा link_follower *follower,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक err, ch;

	err = follower_init(follower);
	अगर (err < 0)
		वापस err;
	क्रम (ch = 0; ch < follower->info.count; ch++)
		ucontrol->value.पूर्णांकeger.value[ch] = follower->vals[ch];
	वापस 0;
पूर्ण

अटल पूर्णांक follower_put_val(काष्ठा link_follower *follower,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक err, ch, vol;

	err = master_init(follower->master);
	अगर (err < 0)
		वापस err;

	चयन (follower->info.type) अणु
	हाल SNDRV_CTL_ELEM_TYPE_BOOLEAN:
		क्रम (ch = 0; ch < follower->info.count; ch++)
			ucontrol->value.पूर्णांकeger.value[ch] &=
				!!follower->master->val;
		अवरोध;
	हाल SNDRV_CTL_ELEM_TYPE_INTEGER:
		क्रम (ch = 0; ch < follower->info.count; ch++) अणु
			/* max master volume is supposed to be 0 dB */
			vol = ucontrol->value.पूर्णांकeger.value[ch];
			vol += follower->master->val - follower->master->info.max_val;
			अगर (vol < follower->info.min_val)
				vol = follower->info.min_val;
			अन्यथा अगर (vol > follower->info.max_val)
				vol = follower->info.max_val;
			ucontrol->value.पूर्णांकeger.value[ch] = vol;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस follower->follower.put(&follower->follower, ucontrol);
पूर्ण

/*
 * ctl callbacks क्रम followers
 */
अटल पूर्णांक follower_info(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा link_follower *follower = snd_kcontrol_chip(kcontrol);
	वापस follower->follower.info(&follower->follower, uinfo);
पूर्ण

अटल पूर्णांक follower_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा link_follower *follower = snd_kcontrol_chip(kcontrol);
	वापस follower_get_val(follower, ucontrol);
पूर्ण

अटल पूर्णांक follower_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा link_follower *follower = snd_kcontrol_chip(kcontrol);
	पूर्णांक err, ch, changed = 0;

	err = follower_init(follower);
	अगर (err < 0)
		वापस err;
	क्रम (ch = 0; ch < follower->info.count; ch++) अणु
		अगर (follower->vals[ch] != ucontrol->value.पूर्णांकeger.value[ch]) अणु
			changed = 1;
			follower->vals[ch] = ucontrol->value.पूर्णांकeger.value[ch];
		पूर्ण
	पूर्ण
	अगर (!changed)
		वापस 0;
	err = follower_put_val(follower, ucontrol);
	अगर (err < 0)
		वापस err;
	वापस 1;
पूर्ण

अटल पूर्णांक follower_tlv_cmd(काष्ठा snd_kcontrol *kcontrol,
			    पूर्णांक op_flag, अचिन्हित पूर्णांक size,
			    अचिन्हित पूर्णांक __user *tlv)
अणु
	काष्ठा link_follower *follower = snd_kcontrol_chip(kcontrol);
	/* FIXME: this assumes that the max volume is 0 dB */
	वापस follower->follower.tlv.c(&follower->follower, op_flag, size, tlv);
पूर्ण

अटल व्योम follower_मुक्त(काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा link_follower *follower = snd_kcontrol_chip(kcontrol);
	अगर (follower->follower.निजी_मुक्त)
		follower->follower.निजी_मुक्त(&follower->follower);
	अगर (follower->master)
		list_del(&follower->list);
	kमुक्त(follower);
पूर्ण

/*
 * Add a follower control to the group with the given master control
 *
 * All followers must be the same type (वापसing the same inक्रमmation
 * via info callback).  The function करोesn't check it, so it's your
 * responsibility.
 *
 * Also, some additional limitations:
 * - at most two channels
 * - logarithmic volume control (dB level), no linear volume
 * - master can only attenuate the volume, no gain
 */
पूर्णांक _snd_ctl_add_follower(काष्ठा snd_kcontrol *master,
			  काष्ठा snd_kcontrol *follower,
			  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा link_master *master_link = snd_kcontrol_chip(master);
	काष्ठा link_follower *srec;

	srec = kzalloc(काष्ठा_size(srec, follower.vd, follower->count),
		       GFP_KERNEL);
	अगर (!srec)
		वापस -ENOMEM;
	srec->kctl = follower;
	srec->follower = *follower;
	स_नकल(srec->follower.vd, follower->vd, follower->count * माप(*follower->vd));
	srec->master = master_link;
	srec->flags = flags;

	/* override callbacks */
	follower->info = follower_info;
	follower->get = follower_get;
	follower->put = follower_put;
	अगर (follower->vd[0].access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK)
		follower->tlv.c = follower_tlv_cmd;
	follower->निजी_data = srec;
	follower->निजी_मुक्त = follower_मुक्त;

	list_add_tail(&srec->list, &master_link->followers);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(_snd_ctl_add_follower);

/*
 * ctl callbacks क्रम master controls
 */
अटल पूर्णांक master_info(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा link_master *master = snd_kcontrol_chip(kcontrol);
	पूर्णांक ret;

	ret = master_init(master);
	अगर (ret < 0)
		वापस ret;
	uinfo->type = master->info.type;
	uinfo->count = master->info.count;
	uinfo->value.पूर्णांकeger.min = master->info.min_val;
	uinfo->value.पूर्णांकeger.max = master->info.max_val;
	वापस 0;
पूर्ण

अटल पूर्णांक master_get(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा link_master *master = snd_kcontrol_chip(kcontrol);
	पूर्णांक err = master_init(master);
	अगर (err < 0)
		वापस err;
	ucontrol->value.पूर्णांकeger.value[0] = master->val;
	वापस 0;
पूर्ण

अटल पूर्णांक sync_followers(काष्ठा link_master *master, पूर्णांक old_val, पूर्णांक new_val)
अणु
	काष्ठा link_follower *follower;
	काष्ठा snd_ctl_elem_value *uval;

	uval = kदो_स्मृति(माप(*uval), GFP_KERNEL);
	अगर (!uval)
		वापस -ENOMEM;
	list_क्रम_each_entry(follower, &master->followers, list) अणु
		master->val = old_val;
		uval->id = follower->follower.id;
		follower_get_val(follower, uval);
		master->val = new_val;
		follower_put_val(follower, uval);
	पूर्ण
	kमुक्त(uval);
	वापस 0;
पूर्ण

अटल पूर्णांक master_put(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा link_master *master = snd_kcontrol_chip(kcontrol);
	पूर्णांक err, new_val, old_val;
	bool first_init;

	err = master_init(master);
	अगर (err < 0)
		वापस err;
	first_init = err;
	old_val = master->val;
	new_val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (new_val == old_val)
		वापस 0;

	err = sync_followers(master, old_val, new_val);
	अगर (err < 0)
		वापस err;
	अगर (master->hook && !first_init)
		master->hook(master->hook_निजी_data, master->val);
	वापस 1;
पूर्ण

अटल व्योम master_मुक्त(काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा link_master *master = snd_kcontrol_chip(kcontrol);
	काष्ठा link_follower *follower, *n;

	/* मुक्त all follower links and retore the original follower kctls */
	list_क्रम_each_entry_safe(follower, n, &master->followers, list) अणु
		काष्ठा snd_kcontrol *sctl = follower->kctl;
		काष्ठा list_head olist = sctl->list;
		स_नकल(sctl, &follower->follower, माप(*sctl));
		स_नकल(sctl->vd, follower->follower.vd,
		       sctl->count * माप(*sctl->vd));
		sctl->list = olist; /* keep the current linked-list */
		kमुक्त(follower);
	पूर्ण
	kमुक्त(master);
पूर्ण


/**
 * snd_ctl_make_भव_master - Create a भव master control
 * @name: name string of the control element to create
 * @tlv: optional TLV पूर्णांक array क्रम dB inक्रमmation
 *
 * Creates a भव master control with the given name string.
 *
 * After creating a vmaster element, you can add the follower controls
 * via snd_ctl_add_follower() or snd_ctl_add_follower_uncached().
 *
 * The optional argument @tlv can be used to specअगरy the TLV inक्रमmation
 * क्रम dB scale of the master control.  It should be a single element
 * with #SNDRV_CTL_TLVT_DB_SCALE, #SNDRV_CTL_TLV_DB_MINMAX or
 * #SNDRV_CTL_TLVT_DB_MINMAX_MUTE type, and should be the max 0dB.
 *
 * Return: The created control element, or %शून्य क्रम errors (ENOMEM).
 */
काष्ठा snd_kcontrol *snd_ctl_make_भव_master(अक्षर *name,
						 स्थिर अचिन्हित पूर्णांक *tlv)
अणु
	काष्ठा link_master *master;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_kcontrol_new knew;

	स_रखो(&knew, 0, माप(knew));
	knew.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	knew.name = name;
	knew.info = master_info;

	master = kzalloc(माप(*master), GFP_KERNEL);
	अगर (!master)
		वापस शून्य;
	INIT_LIST_HEAD(&master->followers);

	kctl = snd_ctl_new1(&knew, master);
	अगर (!kctl) अणु
		kमुक्त(master);
		वापस शून्य;
	पूर्ण
	/* override some callbacks */
	kctl->info = master_info;
	kctl->get = master_get;
	kctl->put = master_put;
	kctl->निजी_मुक्त = master_मुक्त;

	/* additional (स्थिरant) TLV पढ़ो */
	अगर (tlv) अणु
		अचिन्हित पूर्णांक type = tlv[SNDRV_CTL_TLVO_TYPE];
		अगर (type == SNDRV_CTL_TLVT_DB_SCALE ||
		    type == SNDRV_CTL_TLVT_DB_MINMAX ||
		    type == SNDRV_CTL_TLVT_DB_MINMAX_MUTE) अणु
			kctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_TLV_READ;
			स_नकल(master->tlv, tlv, माप(master->tlv));
			kctl->tlv.p = master->tlv;
		पूर्ण
	पूर्ण

	वापस kctl;
पूर्ण
EXPORT_SYMBOL(snd_ctl_make_भव_master);

/**
 * snd_ctl_add_vmaster_hook - Add a hook to a vmaster control
 * @kcontrol: vmaster kctl element
 * @hook: the hook function
 * @निजी_data: the निजी_data poपूर्णांकer to be saved
 *
 * Adds the given hook to the vmaster control element so that it's called
 * at each समय when the value is changed.
 *
 * Return: Zero.
 */
पूर्णांक snd_ctl_add_vmaster_hook(काष्ठा snd_kcontrol *kcontrol,
			     व्योम (*hook)(व्योम *निजी_data, पूर्णांक),
			     व्योम *निजी_data)
अणु
	काष्ठा link_master *master = snd_kcontrol_chip(kcontrol);
	master->hook = hook;
	master->hook_निजी_data = निजी_data;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_ctl_add_vmaster_hook);

/**
 * snd_ctl_sync_vmaster - Sync the vmaster followers and hook
 * @kcontrol: vmaster kctl element
 * @hook_only: sync only the hook
 *
 * Forcibly call the put callback of each follower and call the hook function
 * to synchronize with the current value of the given vmaster element.
 * NOP when शून्य is passed to @kcontrol.
 */
व्योम snd_ctl_sync_vmaster(काष्ठा snd_kcontrol *kcontrol, bool hook_only)
अणु
	काष्ठा link_master *master;
	bool first_init = false;

	अगर (!kcontrol)
		वापस;
	master = snd_kcontrol_chip(kcontrol);
	अगर (!hook_only) अणु
		पूर्णांक err = master_init(master);
		अगर (err < 0)
			वापस;
		first_init = err;
		err = sync_followers(master, master->val, master->val);
		अगर (err < 0)
			वापस;
	पूर्ण

	अगर (master->hook && !first_init)
		master->hook(master->hook_निजी_data, master->val);
पूर्ण
EXPORT_SYMBOL_GPL(snd_ctl_sync_vmaster);

/**
 * snd_ctl_apply_vmaster_followers - Apply function to each vmaster follower
 * @kctl: vmaster kctl element
 * @func: function to apply
 * @arg: optional function argument
 *
 * Apply the function @func to each follower kctl of the given vmaster kctl.
 * Returns 0 अगर successful, or a negative error code.
 */
पूर्णांक snd_ctl_apply_vmaster_followers(काष्ठा snd_kcontrol *kctl,
				    पूर्णांक (*func)(काष्ठा snd_kcontrol *vfollower,
						काष्ठा snd_kcontrol *follower,
						व्योम *arg),
				    व्योम *arg)
अणु
	काष्ठा link_master *master;
	काष्ठा link_follower *follower;
	पूर्णांक err;

	master = snd_kcontrol_chip(kctl);
	err = master_init(master);
	अगर (err < 0)
		वापस err;
	list_क्रम_each_entry(follower, &master->followers, list) अणु
		err = func(follower->kctl, &follower->follower, arg);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_ctl_apply_vmaster_followers);
