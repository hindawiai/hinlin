<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Trace Module (STM) infraकाष्ठाure
 * Copyright (c) 2014, Intel Corporation.
 *
 * STM class implements generic infraकाष्ठाure क्रम  System Trace Module devices
 * as defined in MIPI STPv2 specअगरication.
 */

#समावेश <linux/pm_runसमय.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/compat.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/srcu.h>
#समावेश <linux/slab.h>
#समावेश <linux/sपंचांग.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "stm.h"

#समावेश <uapi/linux/sपंचांग.h>

अटल अचिन्हित पूर्णांक sपंचांग_core_up;

/*
 * The SRCU here makes sure that STM device करोesn't disappear from under a
 * sपंचांग_source_ग_लिखो() caller, which may want to have as little overhead as
 * possible.
 */
अटल काष्ठा srcu_काष्ठा sपंचांग_source_srcu;

अटल sमाप_प्रकार masters_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा sपंचांग_device *sपंचांग = to_sपंचांग_device(dev);
	पूर्णांक ret;

	ret = प्र_लिखो(buf, "%u %u\n", sपंचांग->data->sw_start, sपंचांग->data->sw_end);

	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(masters);

अटल sमाप_प्रकार channels_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा sपंचांग_device *sपंचांग = to_sपंचांग_device(dev);
	पूर्णांक ret;

	ret = प्र_लिखो(buf, "%u\n", sपंचांग->data->sw_nchannels);

	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(channels);

अटल sमाप_प्रकार hw_override_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा sपंचांग_device *sपंचांग = to_sपंचांग_device(dev);
	पूर्णांक ret;

	ret = प्र_लिखो(buf, "%u\n", sपंचांग->data->hw_override);

	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(hw_override);

अटल काष्ठा attribute *sपंचांग_attrs[] = अणु
	&dev_attr_masters.attr,
	&dev_attr_channels.attr,
	&dev_attr_hw_override.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(sपंचांग);

अटल काष्ठा class sपंचांग_class = अणु
	.name		= "stm",
	.dev_groups	= sपंचांग_groups,
पूर्ण;

/**
 * sपंचांग_find_device() - find sपंचांग device by name
 * @buf:	अक्षरacter buffer containing the name
 *
 * This is called when either policy माला_लो asचिन्हित to an sपंचांग device or an
 * sपंचांग_source device माला_लो linked to an sपंचांग device.
 *
 * This grअसल device's reference (get_device()) and module reference, both
 * of which the calling path needs to make sure to drop with sपंचांग_put_device().
 *
 * Return:	sपंचांग device poपूर्णांकer or null अगर lookup failed.
 */
काष्ठा sपंचांग_device *sपंचांग_find_device(स्थिर अक्षर *buf)
अणु
	काष्ठा sपंचांग_device *sपंचांग;
	काष्ठा device *dev;

	अगर (!sपंचांग_core_up)
		वापस शून्य;

	dev = class_find_device_by_name(&sपंचांग_class, buf);
	अगर (!dev)
		वापस शून्य;

	sपंचांग = to_sपंचांग_device(dev);
	अगर (!try_module_get(sपंचांग->owner)) अणु
		/* matches class_find_device() above */
		put_device(dev);
		वापस शून्य;
	पूर्ण

	वापस sपंचांग;
पूर्ण

/**
 * sपंचांग_put_device() - drop references on the sपंचांग device
 * @sपंचांग:	sपंचांग device, previously acquired by sपंचांग_find_device()
 *
 * This drops the module reference and device reference taken by
 * sपंचांग_find_device() or sपंचांग_अक्षर_खोलो().
 */
व्योम sपंचांग_put_device(काष्ठा sपंचांग_device *sपंचांग)
अणु
	module_put(sपंचांग->owner);
	put_device(&sपंचांग->dev);
पूर्ण

/*
 * Internally we only care about software-writable masters here, that is the
 * ones in the range [sपंचांग_data->sw_start..sपंचांग_data..sw_end], however we need
 * original master numbers to be visible बाह्यally, since they are the ones
 * that will appear in the STP stream. Thus, the पूर्णांकernal bookkeeping uses
 * $master - sपंचांग_data->sw_start to reference master descriptors and such.
 */

#घोषणा __sपंचांग_master(_s, _m)				\
	((_s)->masters[(_m) - (_s)->data->sw_start])

अटल अंतरभूत काष्ठा stp_master *
sपंचांग_master(काष्ठा sपंचांग_device *sपंचांग, अचिन्हित पूर्णांक idx)
अणु
	अगर (idx < sपंचांग->data->sw_start || idx > sपंचांग->data->sw_end)
		वापस शून्य;

	वापस __sपंचांग_master(sपंचांग, idx);
पूर्ण

अटल पूर्णांक stp_master_alloc(काष्ठा sपंचांग_device *sपंचांग, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा stp_master *master;

	master = kzalloc(काष्ठा_size(master, chan_map,
				     BITS_TO_LONGS(sपंचांग->data->sw_nchannels)),
			 GFP_ATOMIC);
	अगर (!master)
		वापस -ENOMEM;

	master->nr_मुक्त = sपंचांग->data->sw_nchannels;
	__sपंचांग_master(sपंचांग, idx) = master;

	वापस 0;
पूर्ण

अटल व्योम stp_master_मुक्त(काष्ठा sपंचांग_device *sपंचांग, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा stp_master *master = sपंचांग_master(sपंचांग, idx);

	अगर (!master)
		वापस;

	__sपंचांग_master(sपंचांग, idx) = शून्य;
	kमुक्त(master);
पूर्ण

अटल व्योम sपंचांग_output_claim(काष्ठा sपंचांग_device *sपंचांग, काष्ठा sपंचांग_output *output)
अणु
	काष्ठा stp_master *master = sपंचांग_master(sपंचांग, output->master);

	lockdep_निश्चित_held(&sपंचांग->mc_lock);
	lockdep_निश्चित_held(&output->lock);

	अगर (WARN_ON_ONCE(master->nr_मुक्त < output->nr_chans))
		वापस;

	biपंचांगap_allocate_region(&master->chan_map[0], output->channel,
			       ilog2(output->nr_chans));

	master->nr_मुक्त -= output->nr_chans;
पूर्ण

अटल व्योम
sपंचांग_output_disclaim(काष्ठा sपंचांग_device *sपंचांग, काष्ठा sपंचांग_output *output)
अणु
	काष्ठा stp_master *master = sपंचांग_master(sपंचांग, output->master);

	lockdep_निश्चित_held(&sपंचांग->mc_lock);
	lockdep_निश्चित_held(&output->lock);

	biपंचांगap_release_region(&master->chan_map[0], output->channel,
			      ilog2(output->nr_chans));

	master->nr_मुक्त += output->nr_chans;
	output->nr_chans = 0;
पूर्ण

/*
 * This is like biपंचांगap_find_मुक्त_region(), except it can ignore @start bits
 * at the beginning.
 */
अटल पूर्णांक find_मुक्त_channels(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक start,
			      अचिन्हित पूर्णांक end, अचिन्हित पूर्णांक width)
अणु
	अचिन्हित पूर्णांक pos;
	पूर्णांक i;

	क्रम (pos = start; pos < end + 1; pos = ALIGN(pos, width)) अणु
		pos = find_next_zero_bit(biपंचांगap, end + 1, pos);
		अगर (pos + width > end + 1)
			अवरोध;

		अगर (pos & (width - 1))
			जारी;

		क्रम (i = 1; i < width && !test_bit(pos + i, biपंचांगap); i++)
			;
		अगर (i == width)
			वापस pos;

		/* step over [pos..pos+i) to जारी search */
		pos += i;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक
sपंचांग_find_master_chan(काष्ठा sपंचांग_device *sपंचांग, अचिन्हित पूर्णांक width,
		     अचिन्हित पूर्णांक *mstart, अचिन्हित पूर्णांक mend,
		     अचिन्हित पूर्णांक *cstart, अचिन्हित पूर्णांक cend)
अणु
	काष्ठा stp_master *master;
	अचिन्हित पूर्णांक midx;
	पूर्णांक pos, err;

	क्रम (midx = *mstart; midx <= mend; midx++) अणु
		अगर (!sपंचांग_master(sपंचांग, midx)) अणु
			err = stp_master_alloc(sपंचांग, midx);
			अगर (err)
				वापस err;
		पूर्ण

		master = sपंचांग_master(sपंचांग, midx);

		अगर (!master->nr_मुक्त)
			जारी;

		pos = find_मुक्त_channels(master->chan_map, *cstart, cend,
					 width);
		अगर (pos < 0)
			जारी;

		*mstart = midx;
		*cstart = pos;
		वापस 0;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक sपंचांग_output_assign(काष्ठा sपंचांग_device *sपंचांग, अचिन्हित पूर्णांक width,
			     काष्ठा stp_policy_node *policy_node,
			     काष्ठा sपंचांग_output *output)
अणु
	अचिन्हित पूर्णांक midx, cidx, mend, cend;
	पूर्णांक ret = -EINVAL;

	अगर (width > sपंचांग->data->sw_nchannels)
		वापस -EINVAL;

	/* We no दीर्घer accept policy_node==शून्य here */
	अगर (WARN_ON_ONCE(!policy_node))
		वापस -EINVAL;

	/*
	 * Also, the caller holds reference to policy_node, so it won't
	 * disappear on us.
	 */
	stp_policy_node_get_ranges(policy_node, &midx, &mend, &cidx, &cend);

	spin_lock(&sपंचांग->mc_lock);
	spin_lock(&output->lock);
	/* output is alपढ़ोy asचिन्हित -- shouldn't happen */
	अगर (WARN_ON_ONCE(output->nr_chans))
		जाओ unlock;

	ret = sपंचांग_find_master_chan(sपंचांग, width, &midx, mend, &cidx, cend);
	अगर (ret < 0)
		जाओ unlock;

	output->master = midx;
	output->channel = cidx;
	output->nr_chans = width;
	अगर (sपंचांग->pdrv->output_खोलो) अणु
		व्योम *priv = stp_policy_node_priv(policy_node);

		अगर (WARN_ON_ONCE(!priv))
			जाओ unlock;

		/* configfs subsys mutex is held by the caller */
		ret = sपंचांग->pdrv->output_खोलो(priv, output);
		अगर (ret)
			जाओ unlock;
	पूर्ण

	sपंचांग_output_claim(sपंचांग, output);
	dev_dbg(&sपंचांग->dev, "assigned %u:%u (+%u)\n", midx, cidx, width);

	ret = 0;
unlock:
	अगर (ret)
		output->nr_chans = 0;

	spin_unlock(&output->lock);
	spin_unlock(&sपंचांग->mc_lock);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग_output_मुक्त(काष्ठा sपंचांग_device *sपंचांग, काष्ठा sपंचांग_output *output)
अणु
	spin_lock(&sपंचांग->mc_lock);
	spin_lock(&output->lock);
	अगर (output->nr_chans)
		sपंचांग_output_disclaim(sपंचांग, output);
	अगर (sपंचांग->pdrv && sपंचांग->pdrv->output_बंद)
		sपंचांग->pdrv->output_बंद(output);
	spin_unlock(&output->lock);
	spin_unlock(&sपंचांग->mc_lock);
पूर्ण

अटल व्योम sपंचांग_output_init(काष्ठा sपंचांग_output *output)
अणु
	spin_lock_init(&output->lock);
पूर्ण

अटल पूर्णांक major_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	अचिन्हित पूर्णांक major = *(अचिन्हित पूर्णांक *)data;

	वापस MAJOR(dev->devt) == major;
पूर्ण

/*
 * Framing protocol management
 * Modules can implement STM protocol drivers and (un-)रेजिस्टर them
 * with the STM class framework.
 */
अटल काष्ठा list_head sपंचांग_pdrv_head;
अटल काष्ठा mutex sपंचांग_pdrv_mutex;

काष्ठा sपंचांग_pdrv_entry अणु
	काष्ठा list_head			entry;
	स्थिर काष्ठा sपंचांग_protocol_driver	*pdrv;
	स्थिर काष्ठा config_item_type		*node_type;
पूर्ण;

अटल स्थिर काष्ठा sपंचांग_pdrv_entry *
__sपंचांग_lookup_protocol(स्थिर अक्षर *name)
अणु
	काष्ठा sपंचांग_pdrv_entry *pe;

	/*
	 * If no name is given (शून्य or ""), fall back to "p_basic".
	 */
	अगर (!name || !*name)
		name = "p_basic";

	list_क्रम_each_entry(pe, &sपंचांग_pdrv_head, entry) अणु
		अगर (!म_भेद(name, pe->pdrv->name))
			वापस pe;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक sपंचांग_रेजिस्टर_protocol(स्थिर काष्ठा sपंचांग_protocol_driver *pdrv)
अणु
	काष्ठा sपंचांग_pdrv_entry *pe = शून्य;
	पूर्णांक ret = -ENOMEM;

	mutex_lock(&sपंचांग_pdrv_mutex);

	अगर (__sपंचांग_lookup_protocol(pdrv->name)) अणु
		ret = -EEXIST;
		जाओ unlock;
	पूर्ण

	pe = kzalloc(माप(*pe), GFP_KERNEL);
	अगर (!pe)
		जाओ unlock;

	अगर (pdrv->policy_attr) अणु
		pe->node_type = get_policy_node_type(pdrv->policy_attr);
		अगर (!pe->node_type)
			जाओ unlock;
	पूर्ण

	list_add_tail(&pe->entry, &sपंचांग_pdrv_head);
	pe->pdrv = pdrv;

	ret = 0;
unlock:
	mutex_unlock(&sपंचांग_pdrv_mutex);

	अगर (ret)
		kमुक्त(pe);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग_रेजिस्टर_protocol);

व्योम sपंचांग_unरेजिस्टर_protocol(स्थिर काष्ठा sपंचांग_protocol_driver *pdrv)
अणु
	काष्ठा sपंचांग_pdrv_entry *pe, *iter;

	mutex_lock(&sपंचांग_pdrv_mutex);

	list_क्रम_each_entry_safe(pe, iter, &sपंचांग_pdrv_head, entry) अणु
		अगर (pe->pdrv == pdrv) अणु
			list_del(&pe->entry);

			अगर (pe->node_type) अणु
				kमुक्त(pe->node_type->ct_attrs);
				kमुक्त(pe->node_type);
			पूर्ण
			kमुक्त(pe);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&sपंचांग_pdrv_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग_unरेजिस्टर_protocol);

अटल bool sपंचांग_get_protocol(स्थिर काष्ठा sपंचांग_protocol_driver *pdrv)
अणु
	वापस try_module_get(pdrv->owner);
पूर्ण

व्योम sपंचांग_put_protocol(स्थिर काष्ठा sपंचांग_protocol_driver *pdrv)
अणु
	module_put(pdrv->owner);
पूर्ण

पूर्णांक sपंचांग_lookup_protocol(स्थिर अक्षर *name,
			स्थिर काष्ठा sपंचांग_protocol_driver **pdrv,
			स्थिर काष्ठा config_item_type **node_type)
अणु
	स्थिर काष्ठा sपंचांग_pdrv_entry *pe;

	mutex_lock(&sपंचांग_pdrv_mutex);

	pe = __sपंचांग_lookup_protocol(name);
	अगर (pe && pe->pdrv && sपंचांग_get_protocol(pe->pdrv)) अणु
		*pdrv = pe->pdrv;
		*node_type = pe->node_type;
	पूर्ण

	mutex_unlock(&sपंचांग_pdrv_mutex);

	वापस pe ? 0 : -ENOENT;
पूर्ण

अटल पूर्णांक sपंचांग_अक्षर_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sपंचांग_file *sपंचांगf;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक major = imajor(inode);
	पूर्णांक err = -ENOMEM;

	dev = class_find_device(&sपंचांग_class, शून्य, &major, major_match);
	अगर (!dev)
		वापस -ENODEV;

	sपंचांगf = kzalloc(माप(*sपंचांगf), GFP_KERNEL);
	अगर (!sपंचांगf)
		जाओ err_put_device;

	err = -ENODEV;
	sपंचांग_output_init(&sपंचांगf->output);
	sपंचांगf->sपंचांग = to_sपंचांग_device(dev);

	अगर (!try_module_get(sपंचांगf->sपंचांग->owner))
		जाओ err_मुक्त;

	file->निजी_data = sपंचांगf;

	वापस nonseekable_खोलो(inode, file);

err_मुक्त:
	kमुक्त(sपंचांगf);
err_put_device:
	/* matches class_find_device() above */
	put_device(dev);

	वापस err;
पूर्ण

अटल पूर्णांक sपंचांग_अक्षर_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sपंचांग_file *sपंचांगf = file->निजी_data;
	काष्ठा sपंचांग_device *sपंचांग = sपंचांगf->sपंचांग;

	अगर (sपंचांग->data->unlink)
		sपंचांग->data->unlink(sपंचांग->data, sपंचांगf->output.master,
				  sपंचांगf->output.channel);

	sपंचांग_output_मुक्त(sपंचांग, &sपंचांगf->output);

	/*
	 * matches the sपंचांग_अक्षर_खोलो()'s
	 * class_find_device() + try_module_get()
	 */
	sपंचांग_put_device(sपंचांग);
	kमुक्त(sपंचांगf);

	वापस 0;
पूर्ण

अटल पूर्णांक
sपंचांग_assign_first_policy(काष्ठा sपंचांग_device *sपंचांग, काष्ठा sपंचांग_output *output,
			अक्षर **ids, अचिन्हित पूर्णांक width)
अणु
	काष्ठा stp_policy_node *pn;
	पूर्णांक err, n;

	/*
	 * On success, stp_policy_node_lookup() will वापस holding the
	 * configfs subप्रणाली mutex, which is then released in
	 * stp_policy_node_put(). This allows the pdrv->output_खोलो() in
	 * sपंचांग_output_assign() to serialize against the attribute accessors.
	 */
	क्रम (n = 0, pn = शून्य; ids[n] && !pn; n++)
		pn = stp_policy_node_lookup(sपंचांग, ids[n]);

	अगर (!pn)
		वापस -EINVAL;

	err = sपंचांग_output_assign(sपंचांग, width, pn, output);

	stp_policy_node_put(pn);

	वापस err;
पूर्ण

/**
 * sपंचांग_data_ग_लिखो() - send the given payload as data packets
 * @data:	sपंचांग driver's data
 * @m:		STP master
 * @c:		STP channel
 * @ts_first:	बारtamp the first packet
 * @buf:	data payload buffer
 * @count:	data payload size
 */
sमाप_प्रकार notrace sपंचांग_data_ग_लिखो(काष्ठा sपंचांग_data *data, अचिन्हित पूर्णांक m,
			       अचिन्हित पूर्णांक c, bool ts_first, स्थिर व्योम *buf,
			       माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक flags = ts_first ? STP_PACKET_TIMESTAMPED : 0;
	sमाप_प्रकार sz;
	माप_प्रकार pos;

	क्रम (pos = 0, sz = 0; pos < count; pos += sz) अणु
		sz = min_t(अचिन्हित पूर्णांक, count - pos, 8);
		sz = data->packet(data, m, c, STP_PACKET_DATA, flags, sz,
				  &((u8 *)buf)[pos]);
		अगर (sz <= 0)
			अवरोध;

		अगर (ts_first) अणु
			flags = 0;
			ts_first = false;
		पूर्ण
	पूर्ण

	वापस sz < 0 ? sz : pos;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग_data_ग_लिखो);

अटल sमाप_प्रकार notrace
sपंचांग_ग_लिखो(काष्ठा sपंचांग_device *sपंचांग, काष्ठा sपंचांग_output *output,
	  अचिन्हित पूर्णांक chan, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err;

	/* sपंचांग->pdrv is serialized against policy_mutex */
	अगर (!sपंचांग->pdrv)
		वापस -ENODEV;

	err = sपंचांग->pdrv->ग_लिखो(sपंचांग->data, output, chan, buf, count);
	अगर (err < 0)
		वापस err;

	वापस err;
पूर्ण

अटल sमाप_प्रकार sपंचांग_अक्षर_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा sपंचांग_file *sपंचांगf = file->निजी_data;
	काष्ठा sपंचांग_device *sपंचांग = sपंचांगf->sपंचांग;
	अक्षर *kbuf;
	पूर्णांक err;

	अगर (count + 1 > PAGE_SIZE)
		count = PAGE_SIZE - 1;

	/*
	 * If no m/c have been asचिन्हित to this ग_लिखोr up to this
	 * poपूर्णांक, try to use the task name and "default" policy entries.
	 */
	अगर (!sपंचांगf->output.nr_chans) अणु
		अक्षर comm[माप(current->comm)];
		अक्षर *ids[] = अणु comm, "default", शून्य पूर्ण;

		get_task_comm(comm, current);

		err = sपंचांग_assign_first_policy(sपंचांगf->sपंचांग, &sपंचांगf->output, ids, 1);
		/*
		 * EBUSY means that somebody अन्यथा just asचिन्हित this
		 * output, which is just fine क्रम ग_लिखो()
		 */
		अगर (err)
			वापस err;
	पूर्ण

	kbuf = kदो_स्मृति(count + 1, GFP_KERNEL);
	अगर (!kbuf)
		वापस -ENOMEM;

	err = copy_from_user(kbuf, buf, count);
	अगर (err) अणु
		kमुक्त(kbuf);
		वापस -EFAULT;
	पूर्ण

	pm_runसमय_get_sync(&sपंचांग->dev);

	count = sपंचांग_ग_लिखो(sपंचांग, &sपंचांगf->output, 0, kbuf, count);

	pm_runसमय_mark_last_busy(&sपंचांग->dev);
	pm_runसमय_put_स्वतःsuspend(&sपंचांग->dev);
	kमुक्त(kbuf);

	वापस count;
पूर्ण

अटल व्योम sपंचांग_mmap_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा sपंचांग_file *sपंचांगf = vma->vm_file->निजी_data;
	काष्ठा sपंचांग_device *sपंचांग = sपंचांगf->sपंचांग;

	pm_runसमय_get(&sपंचांग->dev);
पूर्ण

अटल व्योम sपंचांग_mmap_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा sपंचांग_file *sपंचांगf = vma->vm_file->निजी_data;
	काष्ठा sपंचांग_device *sपंचांग = sपंचांगf->sपंचांग;

	pm_runसमय_mark_last_busy(&sपंचांग->dev);
	pm_runसमय_put_स्वतःsuspend(&sपंचांग->dev);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा sपंचांग_mmap_vmops = अणु
	.खोलो	= sपंचांग_mmap_खोलो,
	.बंद	= sपंचांग_mmap_बंद,
पूर्ण;

अटल पूर्णांक sपंचांग_अक्षर_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा sपंचांग_file *sपंचांगf = file->निजी_data;
	काष्ठा sपंचांग_device *sपंचांग = sपंचांगf->sपंचांग;
	अचिन्हित दीर्घ size, phys;

	अगर (!sपंचांग->data->mmio_addr)
		वापस -EOPNOTSUPP;

	अगर (vma->vm_pgoff)
		वापस -EINVAL;

	size = vma->vm_end - vma->vm_start;

	अगर (sपंचांगf->output.nr_chans * sपंचांग->data->sw_mmiosz != size)
		वापस -EINVAL;

	phys = sपंचांग->data->mmio_addr(sपंचांग->data, sपंचांगf->output.master,
				    sपंचांगf->output.channel,
				    sपंचांगf->output.nr_chans);

	अगर (!phys)
		वापस -EINVAL;

	pm_runसमय_get_sync(&sपंचांग->dev);

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_ops = &sपंचांग_mmap_vmops;
	vm_iomap_memory(vma, phys, size);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग_अक्षर_policy_set_ioctl(काष्ठा sपंचांग_file *sपंचांगf, व्योम __user *arg)
अणु
	काष्ठा sपंचांग_device *sपंचांग = sपंचांगf->sपंचांग;
	काष्ठा stp_policy_id *id;
	अक्षर *ids[] = अणु शून्य, शून्य पूर्ण;
	पूर्णांक ret = -EINVAL, wlimit = 1;
	u32 size;

	अगर (sपंचांगf->output.nr_chans)
		वापस -EBUSY;

	अगर (copy_from_user(&size, arg, माप(size)))
		वापस -EFAULT;

	अगर (size < माप(*id) || size >= PATH_MAX + माप(*id))
		वापस -EINVAL;

	/*
	 * size + 1 to make sure the .id string at the bottom is terminated,
	 * which is also why memdup_user() is not useful here
	 */
	id = kzalloc(size + 1, GFP_KERNEL);
	अगर (!id)
		वापस -ENOMEM;

	अगर (copy_from_user(id, arg, size)) अणु
		ret = -EFAULT;
		जाओ err_मुक्त;
	पूर्ण

	अगर (id->__reserved_0 || id->__reserved_1)
		जाओ err_मुक्त;

	अगर (sपंचांग->data->sw_mmiosz)
		wlimit = PAGE_SIZE / sपंचांग->data->sw_mmiosz;

	अगर (id->width < 1 || id->width > wlimit)
		जाओ err_मुक्त;

	ids[0] = id->id;
	ret = sपंचांग_assign_first_policy(sपंचांगf->sपंचांग, &sपंचांगf->output, ids,
				      id->width);
	अगर (ret)
		जाओ err_मुक्त;

	अगर (sपंचांग->data->link)
		ret = sपंचांग->data->link(sपंचांग->data, sपंचांगf->output.master,
				      sपंचांगf->output.channel);

	अगर (ret)
		sपंचांग_output_मुक्त(sपंचांगf->sपंचांग, &sपंचांगf->output);

err_मुक्त:
	kमुक्त(id);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग_अक्षर_policy_get_ioctl(काष्ठा sपंचांग_file *sपंचांगf, व्योम __user *arg)
अणु
	काष्ठा stp_policy_id id = अणु
		.size		= माप(id),
		.master		= sपंचांगf->output.master,
		.channel	= sपंचांगf->output.channel,
		.width		= sपंचांगf->output.nr_chans,
		.__reserved_0	= 0,
		.__reserved_1	= 0,
	पूर्ण;

	वापस copy_to_user(arg, &id, id.size) ? -EFAULT : 0;
पूर्ण

अटल दीर्घ
sपंचांग_अक्षर_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sपंचांग_file *sपंचांगf = file->निजी_data;
	काष्ठा sपंचांग_data *sपंचांग_data = sपंचांगf->sपंचांग->data;
	पूर्णांक err = -ENOTTY;
	u64 options;

	चयन (cmd) अणु
	हाल STP_POLICY_ID_SET:
		err = sपंचांग_अक्षर_policy_set_ioctl(sपंचांगf, (व्योम __user *)arg);
		अगर (err)
			वापस err;

		वापस sपंचांग_अक्षर_policy_get_ioctl(sपंचांगf, (व्योम __user *)arg);

	हाल STP_POLICY_ID_GET:
		वापस sपंचांग_अक्षर_policy_get_ioctl(sपंचांगf, (व्योम __user *)arg);

	हाल STP_SET_OPTIONS:
		अगर (copy_from_user(&options, (u64 __user *)arg, माप(u64)))
			वापस -EFAULT;

		अगर (sपंचांग_data->set_options)
			err = sपंचांग_data->set_options(sपंचांग_data,
						    sपंचांगf->output.master,
						    sपंचांगf->output.channel,
						    sपंचांगf->output.nr_chans,
						    options);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations sपंचांग_fops = अणु
	.खोलो		= sपंचांग_अक्षर_खोलो,
	.release	= sपंचांग_अक्षर_release,
	.ग_लिखो		= sपंचांग_अक्षर_ग_लिखो,
	.mmap		= sपंचांग_अक्षर_mmap,
	.unlocked_ioctl	= sपंचांग_अक्षर_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.llseek		= no_llseek,
पूर्ण;

अटल व्योम sपंचांग_device_release(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग_device *sपंचांग = to_sपंचांग_device(dev);

	vमुक्त(sपंचांग);
पूर्ण

पूर्णांक sपंचांग_रेजिस्टर_device(काष्ठा device *parent, काष्ठा sपंचांग_data *sपंचांग_data,
			काष्ठा module *owner)
अणु
	काष्ठा sपंचांग_device *sपंचांग;
	अचिन्हित पूर्णांक nmasters;
	पूर्णांक err = -ENOMEM;

	अगर (!sपंचांग_core_up)
		वापस -EPROBE_DEFER;

	अगर (!sपंचांग_data->packet || !sपंचांग_data->sw_nchannels)
		वापस -EINVAL;

	nmasters = sपंचांग_data->sw_end - sपंचांग_data->sw_start + 1;
	sपंचांग = vzalloc(माप(*sपंचांग) + nmasters * माप(व्योम *));
	अगर (!sपंचांग)
		वापस -ENOMEM;

	sपंचांग->major = रेजिस्टर_chrdev(0, sपंचांग_data->name, &sपंचांग_fops);
	अगर (sपंचांग->major < 0)
		जाओ err_मुक्त;

	device_initialize(&sपंचांग->dev);
	sपंचांग->dev.devt = MKDEV(sपंचांग->major, 0);
	sपंचांग->dev.class = &sपंचांग_class;
	sपंचांग->dev.parent = parent;
	sपंचांग->dev.release = sपंचांग_device_release;

	mutex_init(&sपंचांग->link_mutex);
	spin_lock_init(&sपंचांग->link_lock);
	INIT_LIST_HEAD(&sपंचांग->link_list);

	/* initialize the object beक्रमe it is accessible via sysfs */
	spin_lock_init(&sपंचांग->mc_lock);
	mutex_init(&sपंचांग->policy_mutex);
	sपंचांग->sw_nmasters = nmasters;
	sपंचांग->owner = owner;
	sपंचांग->data = sपंचांग_data;
	sपंचांग_data->sपंचांग = sपंचांग;

	err = kobject_set_name(&sपंचांग->dev.kobj, "%s", sपंचांग_data->name);
	अगर (err)
		जाओ err_device;

	err = device_add(&sपंचांग->dev);
	अगर (err)
		जाओ err_device;

	/*
	 * Use delayed स्वतःsuspend to aव्योम bouncing back and क्रमth
	 * on recurring अक्षरacter device ग_लिखोs, with the initial
	 * delay समय of 2 seconds.
	 */
	pm_runसमय_no_callbacks(&sपंचांग->dev);
	pm_runसमय_use_स्वतःsuspend(&sपंचांग->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&sपंचांग->dev, 2000);
	pm_runसमय_set_suspended(&sपंचांग->dev);
	pm_runसमय_enable(&sपंचांग->dev);

	वापस 0;

err_device:
	unरेजिस्टर_chrdev(sपंचांग->major, sपंचांग_data->name);

	/* matches device_initialize() above */
	put_device(&sपंचांग->dev);
err_मुक्त:
	vमुक्त(sपंचांग);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग_रेजिस्टर_device);

अटल पूर्णांक __sपंचांग_source_link_drop(काष्ठा sपंचांग_source_device *src,
				  काष्ठा sपंचांग_device *sपंचांग);

व्योम sपंचांग_unरेजिस्टर_device(काष्ठा sपंचांग_data *sपंचांग_data)
अणु
	काष्ठा sपंचांग_device *sपंचांग = sपंचांग_data->sपंचांग;
	काष्ठा sपंचांग_source_device *src, *iter;
	पूर्णांक i, ret;

	pm_runसमय_करोnt_use_स्वतःsuspend(&sपंचांग->dev);
	pm_runसमय_disable(&sपंचांग->dev);

	mutex_lock(&sपंचांग->link_mutex);
	list_क्रम_each_entry_safe(src, iter, &sपंचांग->link_list, link_entry) अणु
		ret = __sपंचांग_source_link_drop(src, sपंचांग);
		/*
		 * src <-> sपंचांग link must not change under the same
		 * sपंचांग::link_mutex, so complain loudly अगर it has;
		 * also in this situation ret!=0 means this src is
		 * not connected to this sपंचांग and it should be otherwise
		 * safe to proceed with the tear-करोwn of sपंचांग.
		 */
		WARN_ON_ONCE(ret);
	पूर्ण
	mutex_unlock(&sपंचांग->link_mutex);

	synchronize_srcu(&sपंचांग_source_srcu);

	unरेजिस्टर_chrdev(sपंचांग->major, sपंचांग_data->name);

	mutex_lock(&sपंचांग->policy_mutex);
	अगर (sपंचांग->policy)
		stp_policy_unbind(sपंचांग->policy);
	mutex_unlock(&sपंचांग->policy_mutex);

	क्रम (i = sपंचांग->data->sw_start; i <= sपंचांग->data->sw_end; i++)
		stp_master_मुक्त(sपंचांग, i);

	device_unरेजिस्टर(&sपंचांग->dev);
	sपंचांग_data->sपंचांग = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग_unरेजिस्टर_device);

/*
 * sपंचांग::link_list access serialization uses a spinlock and a mutex; holding
 * either of them guarantees that the list is stable; modअगरication requires
 * holding both of them.
 *
 * Lock ordering is as follows:
 *   sपंचांग::link_mutex
 *     sपंचांग::link_lock
 *       src::link_lock
 */

/**
 * sपंचांग_source_link_add() - connect an sपंचांग_source device to an sपंचांग device
 * @src:	sपंचांग_source device
 * @sपंचांग:	sपंचांग device
 *
 * This function establishes a link from sपंचांग_source to an sपंचांग device so that
 * the क्रमmer can send out trace data to the latter.
 *
 * Return:	0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक sपंचांग_source_link_add(काष्ठा sपंचांग_source_device *src,
			       काष्ठा sपंचांग_device *sपंचांग)
अणु
	अक्षर *ids[] = अणु शून्य, "default", शून्य पूर्ण;
	पूर्णांक err = -ENOMEM;

	mutex_lock(&sपंचांग->link_mutex);
	spin_lock(&sपंचांग->link_lock);
	spin_lock(&src->link_lock);

	/* src->link is dereferenced under sपंचांग_source_srcu but not the list */
	rcu_assign_poपूर्णांकer(src->link, sपंचांग);
	list_add_tail(&src->link_entry, &sपंचांग->link_list);

	spin_unlock(&src->link_lock);
	spin_unlock(&sपंचांग->link_lock);
	mutex_unlock(&sपंचांग->link_mutex);

	ids[0] = kstrdup(src->data->name, GFP_KERNEL);
	अगर (!ids[0])
		जाओ fail_detach;

	err = sपंचांग_assign_first_policy(sपंचांग, &src->output, ids,
				      src->data->nr_chans);
	kमुक्त(ids[0]);

	अगर (err)
		जाओ fail_detach;

	/* this is to notअगरy the STM device that a new link has been made */
	अगर (sपंचांग->data->link)
		err = sपंचांग->data->link(sपंचांग->data, src->output.master,
				      src->output.channel);

	अगर (err)
		जाओ fail_मुक्त_output;

	/* this is to let the source carry out all necessary preparations */
	अगर (src->data->link)
		src->data->link(src->data);

	वापस 0;

fail_मुक्त_output:
	sपंचांग_output_मुक्त(sपंचांग, &src->output);

fail_detach:
	mutex_lock(&sपंचांग->link_mutex);
	spin_lock(&sपंचांग->link_lock);
	spin_lock(&src->link_lock);

	rcu_assign_poपूर्णांकer(src->link, शून्य);
	list_del_init(&src->link_entry);

	spin_unlock(&src->link_lock);
	spin_unlock(&sपंचांग->link_lock);
	mutex_unlock(&sपंचांग->link_mutex);

	वापस err;
पूर्ण

/**
 * __sपंचांग_source_link_drop() - detach sपंचांग_source from an sपंचांग device
 * @src:	sपंचांग_source device
 * @sपंचांग:	sपंचांग device
 *
 * If @sपंचांग is @src::link, disconnect them from one another and put the
 * reference on the @sपंचांग device.
 *
 * Caller must hold sपंचांग::link_mutex.
 */
अटल पूर्णांक __sपंचांग_source_link_drop(काष्ठा sपंचांग_source_device *src,
				  काष्ठा sपंचांग_device *sपंचांग)
अणु
	काष्ठा sपंचांग_device *link;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&sपंचांग->link_mutex);

	/* क्रम sपंचांग::link_list modअगरication, we hold both mutex and spinlock */
	spin_lock(&sपंचांग->link_lock);
	spin_lock(&src->link_lock);
	link = srcu_dereference_check(src->link, &sपंचांग_source_srcu, 1);

	/*
	 * The linked device may have changed since we last looked, because
	 * we weren't holding the src::link_lock back then; अगर this is the
	 * हाल, tell the caller to retry.
	 */
	अगर (link != sपंचांग) अणु
		ret = -EAGAIN;
		जाओ unlock;
	पूर्ण

	sपंचांग_output_मुक्त(link, &src->output);
	list_del_init(&src->link_entry);
	pm_runसमय_mark_last_busy(&link->dev);
	pm_runसमय_put_स्वतःsuspend(&link->dev);
	/* matches sपंचांग_find_device() from sपंचांग_source_link_store() */
	sपंचांग_put_device(link);
	rcu_assign_poपूर्णांकer(src->link, शून्य);

unlock:
	spin_unlock(&src->link_lock);
	spin_unlock(&sपंचांग->link_lock);

	/*
	 * Call the unlink callbacks क्रम both source and sपंचांग, when we know
	 * that we have actually perक्रमmed the unlinking.
	 */
	अगर (!ret) अणु
		अगर (src->data->unlink)
			src->data->unlink(src->data);

		अगर (sपंचांग->data->unlink)
			sपंचांग->data->unlink(sपंचांग->data, src->output.master,
					  src->output.channel);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sपंचांग_source_link_drop() - detach sपंचांग_source from its sपंचांग device
 * @src:	sपंचांग_source device
 *
 * Unlinking means disconnecting from source's STM device; after this
 * ग_लिखोs will be unsuccessful until it is linked to a new STM device.
 *
 * This will happen on "stm_source_link" sysfs attribute ग_लिखो to unकरो
 * the existing link (अगर any), or on linked STM device's de-registration.
 */
अटल व्योम sपंचांग_source_link_drop(काष्ठा sपंचांग_source_device *src)
अणु
	काष्ठा sपंचांग_device *sपंचांग;
	पूर्णांक idx, ret;

retry:
	idx = srcu_पढ़ो_lock(&sपंचांग_source_srcu);
	/*
	 * The sपंचांग device will be valid क्रम the duration of this
	 * पढ़ो section, but the link may change beक्रमe we grab
	 * the src::link_lock in __sपंचांग_source_link_drop().
	 */
	sपंचांग = srcu_dereference(src->link, &sपंचांग_source_srcu);

	ret = 0;
	अगर (sपंचांग) अणु
		mutex_lock(&sपंचांग->link_mutex);
		ret = __sपंचांग_source_link_drop(src, sपंचांग);
		mutex_unlock(&sपंचांग->link_mutex);
	पूर्ण

	srcu_पढ़ो_unlock(&sपंचांग_source_srcu, idx);

	/* अगर it did change, retry */
	अगर (ret == -EAGAIN)
		जाओ retry;
पूर्ण

अटल sमाप_प्रकार sपंचांग_source_link_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा sपंचांग_source_device *src = to_sपंचांग_source_device(dev);
	काष्ठा sपंचांग_device *sपंचांग;
	पूर्णांक idx, ret;

	idx = srcu_पढ़ो_lock(&sपंचांग_source_srcu);
	sपंचांग = srcu_dereference(src->link, &sपंचांग_source_srcu);
	ret = प्र_लिखो(buf, "%s\n",
		      sपंचांग ? dev_name(&sपंचांग->dev) : "<none>");
	srcu_पढ़ो_unlock(&sपंचांग_source_srcu, idx);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार sपंचांग_source_link_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sपंचांग_source_device *src = to_sपंचांग_source_device(dev);
	काष्ठा sपंचांग_device *link;
	पूर्णांक err;

	sपंचांग_source_link_drop(src);

	link = sपंचांग_find_device(buf);
	अगर (!link)
		वापस -EINVAL;

	pm_runसमय_get(&link->dev);

	err = sपंचांग_source_link_add(src, link);
	अगर (err) अणु
		pm_runसमय_put_स्वतःsuspend(&link->dev);
		/* matches the sपंचांग_find_device() above */
		sपंचांग_put_device(link);
	पूर्ण

	वापस err ? : count;
पूर्ण

अटल DEVICE_ATTR_RW(sपंचांग_source_link);

अटल काष्ठा attribute *sपंचांग_source_attrs[] = अणु
	&dev_attr_sपंचांग_source_link.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(sपंचांग_source);

अटल काष्ठा class sपंचांग_source_class = अणु
	.name		= "stm_source",
	.dev_groups	= sपंचांग_source_groups,
पूर्ण;

अटल व्योम sपंचांग_source_device_release(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग_source_device *src = to_sपंचांग_source_device(dev);

	kमुक्त(src);
पूर्ण

/**
 * sपंचांग_source_रेजिस्टर_device() - रेजिस्टर an sपंचांग_source device
 * @parent:	parent device
 * @data:	device description काष्ठाure
 *
 * This will create a device of sपंचांग_source class that can ग_लिखो
 * data to an sपंचांग device once linked.
 *
 * Return:	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक sपंचांग_source_रेजिस्टर_device(काष्ठा device *parent,
			       काष्ठा sपंचांग_source_data *data)
अणु
	काष्ठा sपंचांग_source_device *src;
	पूर्णांक err;

	अगर (!sपंचांग_core_up)
		वापस -EPROBE_DEFER;

	src = kzalloc(माप(*src), GFP_KERNEL);
	अगर (!src)
		वापस -ENOMEM;

	device_initialize(&src->dev);
	src->dev.class = &sपंचांग_source_class;
	src->dev.parent = parent;
	src->dev.release = sपंचांग_source_device_release;

	err = kobject_set_name(&src->dev.kobj, "%s", data->name);
	अगर (err)
		जाओ err;

	pm_runसमय_no_callbacks(&src->dev);
	pm_runसमय_क्रमbid(&src->dev);

	err = device_add(&src->dev);
	अगर (err)
		जाओ err;

	sपंचांग_output_init(&src->output);
	spin_lock_init(&src->link_lock);
	INIT_LIST_HEAD(&src->link_entry);
	src->data = data;
	data->src = src;

	वापस 0;

err:
	put_device(&src->dev);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग_source_रेजिस्टर_device);

/**
 * sपंचांग_source_unरेजिस्टर_device() - unरेजिस्टर an sपंचांग_source device
 * @data:	device description that was used to रेजिस्टर the device
 *
 * This will हटाओ a previously created sपंचांग_source device from the प्रणाली.
 */
व्योम sपंचांग_source_unरेजिस्टर_device(काष्ठा sपंचांग_source_data *data)
अणु
	काष्ठा sपंचांग_source_device *src = data->src;

	sपंचांग_source_link_drop(src);

	device_unरेजिस्टर(&src->dev);
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग_source_unरेजिस्टर_device);

पूर्णांक notrace sपंचांग_source_ग_लिखो(काष्ठा sपंचांग_source_data *data,
			     अचिन्हित पूर्णांक chan,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sपंचांग_source_device *src = data->src;
	काष्ठा sपंचांग_device *sपंचांग;
	पूर्णांक idx;

	अगर (!src->output.nr_chans)
		वापस -ENODEV;

	अगर (chan >= src->output.nr_chans)
		वापस -EINVAL;

	idx = srcu_पढ़ो_lock(&sपंचांग_source_srcu);

	sपंचांग = srcu_dereference(src->link, &sपंचांग_source_srcu);
	अगर (sपंचांग)
		count = sपंचांग_ग_लिखो(sपंचांग, &src->output, chan, buf, count);
	अन्यथा
		count = -ENODEV;

	srcu_पढ़ो_unlock(&sपंचांग_source_srcu, idx);

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग_source_ग_लिखो);

अटल पूर्णांक __init sपंचांग_core_init(व्योम)
अणु
	पूर्णांक err;

	err = class_रेजिस्टर(&sपंचांग_class);
	अगर (err)
		वापस err;

	err = class_रेजिस्टर(&sपंचांग_source_class);
	अगर (err)
		जाओ err_sपंचांग;

	err = stp_configfs_init();
	अगर (err)
		जाओ err_src;

	init_srcu_काष्ठा(&sपंचांग_source_srcu);
	INIT_LIST_HEAD(&sपंचांग_pdrv_head);
	mutex_init(&sपंचांग_pdrv_mutex);

	/*
	 * So as to not confuse existing users with a requirement
	 * to load yet another module, करो it here.
	 */
	अगर (IS_ENABLED(CONFIG_STM_PROTO_BASIC))
		(व्योम)request_module_noरुको("stm_p_basic");
	sपंचांग_core_up++;

	वापस 0;

err_src:
	class_unरेजिस्टर(&sपंचांग_source_class);
err_sपंचांग:
	class_unरेजिस्टर(&sपंचांग_class);

	वापस err;
पूर्ण

module_init(sपंचांग_core_init);

अटल व्योम __निकास sपंचांग_core_निकास(व्योम)
अणु
	cleanup_srcu_काष्ठा(&sपंचांग_source_srcu);
	class_unरेजिस्टर(&sपंचांग_source_class);
	class_unरेजिस्टर(&sपंचांग_class);
	stp_configfs_निकास();
पूर्ण

module_निकास(sपंचांग_core_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("System Trace Module device class");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@linux.intel.com>");
