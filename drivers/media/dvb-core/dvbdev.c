<शैली गुरु>
/*
 * dvbdev.c
 *
 * Copyright (C) 2000 Ralph  Metzler <ralph@convergence.de>
 *                  & Marcus Metzler <marcus@convergence.de>
 *                    क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#घोषणा pr_fmt(fmt) "dvbdev: " fmt

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/cdev.h>
#समावेश <linux/mutex.h>
#समावेश <media/dvbdev.h>

/* Due to क्रमागत tuner_pad_index */
#समावेश <media/tuner.h>

अटल DEFINE_MUTEX(dvbdev_mutex);
अटल पूर्णांक dvbdev_debug;

module_param(dvbdev_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(dvbdev_debug, "Turn on/off device debugging (default:off).");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (dvbdev_debug)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

अटल LIST_HEAD(dvb_adapter_list);
अटल DEFINE_MUTEX(dvbdev_रेजिस्टर_lock);

अटल स्थिर अक्षर * स्थिर dnames[] = अणु
	[DVB_DEVICE_VIDEO] =		"video",
	[DVB_DEVICE_AUDIO] =		"audio",
	[DVB_DEVICE_SEC] =		"sec",
	[DVB_DEVICE_FRONTEND] =		"frontend",
	[DVB_DEVICE_DEMUX] =		"demux",
	[DVB_DEVICE_DVR] =		"dvr",
	[DVB_DEVICE_CA] =		"ca",
	[DVB_DEVICE_NET] =		"net",
	[DVB_DEVICE_OSD] =		"osd"
पूर्ण;

#अगर_घोषित CONFIG_DVB_DYNAMIC_MINORS
#घोषणा MAX_DVB_MINORS		256
#घोषणा DVB_MAX_IDS		MAX_DVB_MINORS
#अन्यथा
#घोषणा DVB_MAX_IDS		4

अटल स्थिर u8 minor_type[] = अणु
       [DVB_DEVICE_VIDEO]      = 0,
       [DVB_DEVICE_AUDIO]      = 1,
       [DVB_DEVICE_SEC]        = 2,
       [DVB_DEVICE_FRONTEND]   = 3,
       [DVB_DEVICE_DEMUX]      = 4,
       [DVB_DEVICE_DVR]        = 5,
       [DVB_DEVICE_CA]         = 6,
       [DVB_DEVICE_NET]        = 7,
       [DVB_DEVICE_OSD]        = 8,
पूर्ण;

#घोषणा nums2minor(num, type, id) \
       (((num) << 6) | ((id) << 4) | minor_type[type])

#घोषणा MAX_DVB_MINORS		(DVB_MAX_ADAPTERS*64)
#पूर्ण_अगर

अटल काष्ठा class *dvb_class;

अटल काष्ठा dvb_device *dvb_minors[MAX_DVB_MINORS];
अटल DECLARE_RWSEM(minor_rwsem);

अटल पूर्णांक dvb_device_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev;

	mutex_lock(&dvbdev_mutex);
	करोwn_पढ़ो(&minor_rwsem);
	dvbdev = dvb_minors[iminor(inode)];

	अगर (dvbdev && dvbdev->fops) अणु
		पूर्णांक err = 0;
		स्थिर काष्ठा file_operations *new_fops;

		new_fops = fops_get(dvbdev->fops);
		अगर (!new_fops)
			जाओ fail;
		file->निजी_data = dvbdev;
		replace_fops(file, new_fops);
		अगर (file->f_op->खोलो)
			err = file->f_op->खोलो(inode, file);
		up_पढ़ो(&minor_rwsem);
		mutex_unlock(&dvbdev_mutex);
		वापस err;
	पूर्ण
fail:
	up_पढ़ो(&minor_rwsem);
	mutex_unlock(&dvbdev_mutex);
	वापस -ENODEV;
पूर्ण


अटल स्थिर काष्ठा file_operations dvb_device_fops =
अणु
	.owner =	THIS_MODULE,
	.खोलो =		dvb_device_खोलो,
	.llseek =	noop_llseek,
पूर्ण;

अटल काष्ठा cdev dvb_device_cdev;

पूर्णांक dvb_generic_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;

	अगर (!dvbdev)
		वापस -ENODEV;

	अगर (!dvbdev->users)
		वापस -EBUSY;

	अगर ((file->f_flags & O_ACCMODE) == O_RDONLY) अणु
		अगर (!dvbdev->पढ़ोers)
			वापस -EBUSY;
		dvbdev->पढ़ोers--;
	पूर्ण अन्यथा अणु
		अगर (!dvbdev->ग_लिखोrs)
			वापस -EBUSY;
		dvbdev->ग_लिखोrs--;
	पूर्ण

	dvbdev->users--;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dvb_generic_खोलो);


पूर्णांक dvb_generic_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;

	अगर (!dvbdev)
		वापस -ENODEV;

	अगर ((file->f_flags & O_ACCMODE) == O_RDONLY) अणु
		dvbdev->पढ़ोers++;
	पूर्ण अन्यथा अणु
		dvbdev->ग_लिखोrs++;
	पूर्ण

	dvbdev->users++;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dvb_generic_release);


दीर्घ dvb_generic_ioctl(काष्ठा file *file,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;

	अगर (!dvbdev)
		वापस -ENODEV;

	अगर (!dvbdev->kernel_ioctl)
		वापस -EINVAL;

	वापस dvb_usercopy(file, cmd, arg, dvbdev->kernel_ioctl);
पूर्ण
EXPORT_SYMBOL(dvb_generic_ioctl);


अटल पूर्णांक dvbdev_get_मुक्त_id (काष्ठा dvb_adapter *adap, पूर्णांक type)
अणु
	u32 id = 0;

	जबतक (id < DVB_MAX_IDS) अणु
		काष्ठा dvb_device *dev;
		list_क्रम_each_entry(dev, &adap->device_list, list_head)
			अगर (dev->type == type && dev->id == id)
				जाओ skip;
		वापस id;
skip:
		id++;
	पूर्ण
	वापस -ENखाता;
पूर्ण

अटल व्योम dvb_media_device_मुक्त(काष्ठा dvb_device *dvbdev)
अणु
#अगर defined(CONFIG_MEDIA_CONTROLLER_DVB)
	अगर (dvbdev->entity) अणु
		media_device_unरेजिस्टर_entity(dvbdev->entity);
		kमुक्त(dvbdev->entity);
		kमुक्त(dvbdev->pads);
		dvbdev->entity = शून्य;
		dvbdev->pads = शून्य;
	पूर्ण

	अगर (dvbdev->tsout_entity) अणु
		पूर्णांक i;

		क्रम (i = 0; i < dvbdev->tsout_num_entities; i++) अणु
			media_device_unरेजिस्टर_entity(&dvbdev->tsout_entity[i]);
			kमुक्त(dvbdev->tsout_entity[i].name);
		पूर्ण
		kमुक्त(dvbdev->tsout_entity);
		kमुक्त(dvbdev->tsout_pads);
		dvbdev->tsout_entity = शून्य;
		dvbdev->tsout_pads = शून्य;

		dvbdev->tsout_num_entities = 0;
	पूर्ण

	अगर (dvbdev->पूर्णांकf_devnode) अणु
		media_devnode_हटाओ(dvbdev->पूर्णांकf_devnode);
		dvbdev->पूर्णांकf_devnode = शून्य;
	पूर्ण

	अगर (dvbdev->adapter->conn) अणु
		media_device_unरेजिस्टर_entity(dvbdev->adapter->conn);
		kमुक्त(dvbdev->adapter->conn);
		dvbdev->adapter->conn = शून्य;
		kमुक्त(dvbdev->adapter->conn_pads);
		dvbdev->adapter->conn_pads = शून्य;
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर defined(CONFIG_MEDIA_CONTROLLER_DVB)
अटल पूर्णांक dvb_create_tsout_entity(काष्ठा dvb_device *dvbdev,
				    स्थिर अक्षर *name, पूर्णांक npads)
अणु
	पूर्णांक i, ret = 0;

	dvbdev->tsout_pads = kसुस्मृति(npads, माप(*dvbdev->tsout_pads),
				     GFP_KERNEL);
	अगर (!dvbdev->tsout_pads)
		वापस -ENOMEM;

	dvbdev->tsout_entity = kसुस्मृति(npads, माप(*dvbdev->tsout_entity),
				       GFP_KERNEL);
	अगर (!dvbdev->tsout_entity)
		वापस -ENOMEM;

	dvbdev->tsout_num_entities = npads;

	क्रम (i = 0; i < npads; i++) अणु
		काष्ठा media_pad *pads = &dvbdev->tsout_pads[i];
		काष्ठा media_entity *entity = &dvbdev->tsout_entity[i];

		entity->name = kaप्र_लिखो(GFP_KERNEL, "%s #%d", name, i);
		अगर (!entity->name)
			वापस -ENOMEM;

		entity->function = MEDIA_ENT_F_IO_DTV;
		pads->flags = MEDIA_PAD_FL_SINK;

		ret = media_entity_pads_init(entity, 1, pads);
		अगर (ret < 0)
			वापस ret;

		ret = media_device_रेजिस्टर_entity(dvbdev->adapter->mdev,
						   entity);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा DEMUX_TSOUT	"demux-tsout"
#घोषणा DVR_TSOUT	"dvr-tsout"

अटल पूर्णांक dvb_create_media_entity(काष्ठा dvb_device *dvbdev,
				   पूर्णांक type, पूर्णांक demux_sink_pads)
अणु
	पूर्णांक i, ret, npads;

	चयन (type) अणु
	हाल DVB_DEVICE_FRONTEND:
		npads = 2;
		अवरोध;
	हाल DVB_DEVICE_DVR:
		ret = dvb_create_tsout_entity(dvbdev, DVR_TSOUT,
					      demux_sink_pads);
		वापस ret;
	हाल DVB_DEVICE_DEMUX:
		npads = 1 + demux_sink_pads;
		ret = dvb_create_tsout_entity(dvbdev, DEMUX_TSOUT,
					      demux_sink_pads);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल DVB_DEVICE_CA:
		npads = 2;
		अवरोध;
	हाल DVB_DEVICE_NET:
		/*
		 * We should be creating entities क्रम the MPE/ULE
		 * decapsulation hardware (or software implementation).
		 *
		 * However, the number of क्रम the MPE/ULE decaps may not be
		 * fixed. As we करोn't have yet dynamic support क्रम PADs at
		 * the Media Controller, let's not create the decap
		 * entities yet.
		 */
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण

	dvbdev->entity = kzalloc(माप(*dvbdev->entity), GFP_KERNEL);
	अगर (!dvbdev->entity)
		वापस -ENOMEM;

	dvbdev->entity->name = dvbdev->name;

	अगर (npads) अणु
		dvbdev->pads = kसुस्मृति(npads, माप(*dvbdev->pads),
				       GFP_KERNEL);
		अगर (!dvbdev->pads) अणु
			kमुक्त(dvbdev->entity);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	चयन (type) अणु
	हाल DVB_DEVICE_FRONTEND:
		dvbdev->entity->function = MEDIA_ENT_F_DTV_DEMOD;
		dvbdev->pads[0].flags = MEDIA_PAD_FL_SINK;
		dvbdev->pads[1].flags = MEDIA_PAD_FL_SOURCE;
		अवरोध;
	हाल DVB_DEVICE_DEMUX:
		dvbdev->entity->function = MEDIA_ENT_F_TS_DEMUX;
		dvbdev->pads[0].flags = MEDIA_PAD_FL_SINK;
		क्रम (i = 1; i < npads; i++)
			dvbdev->pads[i].flags = MEDIA_PAD_FL_SOURCE;
		अवरोध;
	हाल DVB_DEVICE_CA:
		dvbdev->entity->function = MEDIA_ENT_F_DTV_CA;
		dvbdev->pads[0].flags = MEDIA_PAD_FL_SINK;
		dvbdev->pads[1].flags = MEDIA_PAD_FL_SOURCE;
		अवरोध;
	शेष:
		/* Should never happen, as the first चयन prevents it */
		kमुक्त(dvbdev->entity);
		kमुक्त(dvbdev->pads);
		dvbdev->entity = शून्य;
		dvbdev->pads = शून्य;
		वापस 0;
	पूर्ण

	अगर (npads) अणु
		ret = media_entity_pads_init(dvbdev->entity, npads, dvbdev->pads);
		अगर (ret)
			वापस ret;
	पूर्ण
	ret = media_device_रेजिस्टर_entity(dvbdev->adapter->mdev,
					   dvbdev->entity);
	अगर (ret)
		वापस ret;

	pr_info("%s: media entity '%s' registered.\n",
		__func__, dvbdev->entity->name);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dvb_रेजिस्टर_media_device(काष्ठा dvb_device *dvbdev,
				     पूर्णांक type, पूर्णांक minor,
				     अचिन्हित demux_sink_pads)
अणु
#अगर defined(CONFIG_MEDIA_CONTROLLER_DVB)
	काष्ठा media_link *link;
	u32 पूर्णांकf_type;
	पूर्णांक ret;

	अगर (!dvbdev->adapter->mdev)
		वापस 0;

	ret = dvb_create_media_entity(dvbdev, type, demux_sink_pads);
	अगर (ret)
		वापस ret;

	चयन (type) अणु
	हाल DVB_DEVICE_FRONTEND:
		पूर्णांकf_type = MEDIA_INTF_T_DVB_FE;
		अवरोध;
	हाल DVB_DEVICE_DEMUX:
		पूर्णांकf_type = MEDIA_INTF_T_DVB_DEMUX;
		अवरोध;
	हाल DVB_DEVICE_DVR:
		पूर्णांकf_type = MEDIA_INTF_T_DVB_DVR;
		अवरोध;
	हाल DVB_DEVICE_CA:
		पूर्णांकf_type = MEDIA_INTF_T_DVB_CA;
		अवरोध;
	हाल DVB_DEVICE_NET:
		पूर्णांकf_type = MEDIA_INTF_T_DVB_NET;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	dvbdev->पूर्णांकf_devnode = media_devnode_create(dvbdev->adapter->mdev,
						    पूर्णांकf_type, 0,
						    DVB_MAJOR, minor);

	अगर (!dvbdev->पूर्णांकf_devnode)
		वापस -ENOMEM;

	/*
	 * Create the "obvious" link, e. g. the ones that represent
	 * a direct association between an पूर्णांकerface and an entity.
	 * Other links should be created अन्यथाwhere, like:
	 *		DVB FE पूर्णांकf    -> tuner
	 *		DVB demux पूर्णांकf -> dvr
	 */

	अगर (!dvbdev->entity)
		वापस 0;

	link = media_create_पूर्णांकf_link(dvbdev->entity,
				      &dvbdev->पूर्णांकf_devnode->पूर्णांकf,
				      MEDIA_LNK_FL_ENABLED |
				      MEDIA_LNK_FL_IMMUTABLE);
	अगर (!link)
		वापस -ENOMEM;
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक dvb_रेजिस्टर_device(काष्ठा dvb_adapter *adap, काष्ठा dvb_device **pdvbdev,
			स्थिर काष्ठा dvb_device *ढाँचा, व्योम *priv,
			क्रमागत dvb_device_type type, पूर्णांक demux_sink_pads)
अणु
	काष्ठा dvb_device *dvbdev;
	काष्ठा file_operations *dvbdevfops;
	काष्ठा device *clsdev;
	पूर्णांक minor;
	पूर्णांक id, ret;

	mutex_lock(&dvbdev_रेजिस्टर_lock);

	अगर ((id = dvbdev_get_मुक्त_id (adap, type)) < 0)अणु
		mutex_unlock(&dvbdev_रेजिस्टर_lock);
		*pdvbdev = शून्य;
		pr_err("%s: couldn't find free device id\n", __func__);
		वापस -ENखाता;
	पूर्ण

	*pdvbdev = dvbdev = kzalloc(माप(*dvbdev), GFP_KERNEL);

	अगर (!dvbdev)अणु
		mutex_unlock(&dvbdev_रेजिस्टर_lock);
		वापस -ENOMEM;
	पूर्ण

	dvbdevfops = kmemdup(ढाँचा->fops, माप(*dvbdevfops), GFP_KERNEL);

	अगर (!dvbdevfops)अणु
		kमुक्त (dvbdev);
		mutex_unlock(&dvbdev_रेजिस्टर_lock);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(dvbdev, ढाँचा, माप(काष्ठा dvb_device));
	dvbdev->type = type;
	dvbdev->id = id;
	dvbdev->adapter = adap;
	dvbdev->priv = priv;
	dvbdev->fops = dvbdevfops;
	init_रुकोqueue_head (&dvbdev->रुको_queue);

	dvbdevfops->owner = adap->module;

	list_add_tail (&dvbdev->list_head, &adap->device_list);

	करोwn_ग_लिखो(&minor_rwsem);
#अगर_घोषित CONFIG_DVB_DYNAMIC_MINORS
	क्रम (minor = 0; minor < MAX_DVB_MINORS; minor++)
		अगर (dvb_minors[minor] == शून्य)
			अवरोध;

	अगर (minor == MAX_DVB_MINORS) अणु
		kमुक्त(dvbdevfops);
		kमुक्त(dvbdev);
		up_ग_लिखो(&minor_rwsem);
		mutex_unlock(&dvbdev_रेजिस्टर_lock);
		वापस -EINVAL;
	पूर्ण
#अन्यथा
	minor = nums2minor(adap->num, type, id);
#पूर्ण_अगर

	dvbdev->minor = minor;
	dvb_minors[minor] = dvbdev;
	up_ग_लिखो(&minor_rwsem);

	ret = dvb_रेजिस्टर_media_device(dvbdev, type, minor, demux_sink_pads);
	अगर (ret) अणु
		pr_err("%s: dvb_register_media_device failed to create the mediagraph\n",
		      __func__);

		dvb_media_device_मुक्त(dvbdev);
		kमुक्त(dvbdevfops);
		kमुक्त(dvbdev);
		mutex_unlock(&dvbdev_रेजिस्टर_lock);
		वापस ret;
	पूर्ण

	mutex_unlock(&dvbdev_रेजिस्टर_lock);

	clsdev = device_create(dvb_class, adap->device,
			       MKDEV(DVB_MAJOR, minor),
			       dvbdev, "dvb%d.%s%d", adap->num, dnames[type], id);
	अगर (IS_ERR(clsdev)) अणु
		pr_err("%s: failed to create device dvb%d.%s%d (%ld)\n",
		       __func__, adap->num, dnames[type], id, PTR_ERR(clsdev));
		dvb_media_device_मुक्त(dvbdev);
		kमुक्त(dvbdevfops);
		kमुक्त(dvbdev);
		वापस PTR_ERR(clsdev);
	पूर्ण
	dprपूर्णांकk("DVB: register adapter%d/%s%d @ minor: %i (0x%02x)\n",
		adap->num, dnames[type], id, minor, minor);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dvb_रेजिस्टर_device);


व्योम dvb_हटाओ_device(काष्ठा dvb_device *dvbdev)
अणु
	अगर (!dvbdev)
		वापस;

	करोwn_ग_लिखो(&minor_rwsem);
	dvb_minors[dvbdev->minor] = शून्य;
	up_ग_लिखो(&minor_rwsem);

	dvb_media_device_मुक्त(dvbdev);

	device_destroy(dvb_class, MKDEV(DVB_MAJOR, dvbdev->minor));

	list_del (&dvbdev->list_head);
पूर्ण
EXPORT_SYMBOL(dvb_हटाओ_device);


व्योम dvb_मुक्त_device(काष्ठा dvb_device *dvbdev)
अणु
	अगर (!dvbdev)
		वापस;

	kमुक्त (dvbdev->fops);
	kमुक्त (dvbdev);
पूर्ण
EXPORT_SYMBOL(dvb_मुक्त_device);


व्योम dvb_unरेजिस्टर_device(काष्ठा dvb_device *dvbdev)
अणु
	dvb_हटाओ_device(dvbdev);
	dvb_मुक्त_device(dvbdev);
पूर्ण
EXPORT_SYMBOL(dvb_unरेजिस्टर_device);


#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB

अटल पूर्णांक dvb_create_io_पूर्णांकf_links(काष्ठा dvb_adapter *adap,
				    काष्ठा media_पूर्णांकerface *पूर्णांकf,
				    अक्षर *name)
अणु
	काष्ठा media_device *mdev = adap->mdev;
	काष्ठा media_entity *entity;
	काष्ठा media_link *link;

	media_device_क्रम_each_entity(entity, mdev) अणु
		अगर (entity->function == MEDIA_ENT_F_IO_DTV) अणु
			अगर (म_भेदन(entity->name, name, म_माप(name)))
				जारी;
			link = media_create_पूर्णांकf_link(entity, पूर्णांकf,
						      MEDIA_LNK_FL_ENABLED |
						      MEDIA_LNK_FL_IMMUTABLE);
			अगर (!link)
				वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक dvb_create_media_graph(काष्ठा dvb_adapter *adap,
			   bool create_rf_connector)
अणु
	काष्ठा media_device *mdev = adap->mdev;
	काष्ठा media_entity *entity, *tuner = शून्य, *demod = शून्य, *conn;
	काष्ठा media_entity *demux = शून्य, *ca = शून्य;
	काष्ठा media_link *link;
	काष्ठा media_पूर्णांकerface *पूर्णांकf;
	अचिन्हित demux_pad = 0;
	अचिन्हित dvr_pad = 0;
	अचिन्हित ntuner = 0, ndemod = 0;
	पूर्णांक ret, pad_source, pad_sink;
	अटल स्थिर अक्षर *connector_name = "Television";

	अगर (!mdev)
		वापस 0;

	media_device_क्रम_each_entity(entity, mdev) अणु
		चयन (entity->function) अणु
		हाल MEDIA_ENT_F_TUNER:
			tuner = entity;
			ntuner++;
			अवरोध;
		हाल MEDIA_ENT_F_DTV_DEMOD:
			demod = entity;
			ndemod++;
			अवरोध;
		हाल MEDIA_ENT_F_TS_DEMUX:
			demux = entity;
			अवरोध;
		हाल MEDIA_ENT_F_DTV_CA:
			ca = entity;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Prepare to संकेतize to media_create_pad_links() that multiple
	 * entities of the same type exists and a 1:n or n:1 links need to be
	 * created.
	 * NOTE: अगर both tuner and demod have multiple instances, it is up
	 * to the caller driver to create such links.
	 */
	अगर (ntuner > 1)
		tuner = शून्य;
	अगर (ndemod > 1)
		demod = शून्य;

	अगर (create_rf_connector) अणु
		conn = kzalloc(माप(*conn), GFP_KERNEL);
		अगर (!conn)
			वापस -ENOMEM;
		adap->conn = conn;

		adap->conn_pads = kzalloc(माप(*adap->conn_pads), GFP_KERNEL);
		अगर (!adap->conn_pads)
			वापस -ENOMEM;

		conn->flags = MEDIA_ENT_FL_CONNECTOR;
		conn->function = MEDIA_ENT_F_CONN_RF;
		conn->name = connector_name;
		adap->conn_pads->flags = MEDIA_PAD_FL_SOURCE;

		ret = media_entity_pads_init(conn, 1, adap->conn_pads);
		अगर (ret)
			वापस ret;

		ret = media_device_रेजिस्टर_entity(mdev, conn);
		अगर (ret)
			वापस ret;

		अगर (!ntuner) अणु
			ret = media_create_pad_links(mdev,
						     MEDIA_ENT_F_CONN_RF,
						     conn, 0,
						     MEDIA_ENT_F_DTV_DEMOD,
						     demod, 0,
						     MEDIA_LNK_FL_ENABLED,
						     false);
		पूर्ण अन्यथा अणु
			pad_sink = media_get_pad_index(tuner, true,
						       PAD_SIGNAL_ANALOG);
			अगर (pad_sink < 0)
				वापस -EINVAL;
			ret = media_create_pad_links(mdev,
						     MEDIA_ENT_F_CONN_RF,
						     conn, 0,
						     MEDIA_ENT_F_TUNER,
						     tuner, pad_sink,
						     MEDIA_LNK_FL_ENABLED,
						     false);
		पूर्ण
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (ntuner && ndemod) अणु
		/* NOTE: first found tuner source pad presumed correct */
		pad_source = media_get_pad_index(tuner, false,
						 PAD_SIGNAL_ANALOG);
		अगर (pad_source < 0)
			वापस -EINVAL;
		ret = media_create_pad_links(mdev,
					     MEDIA_ENT_F_TUNER,
					     tuner, pad_source,
					     MEDIA_ENT_F_DTV_DEMOD,
					     demod, 0, MEDIA_LNK_FL_ENABLED,
					     false);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (ndemod && demux) अणु
		ret = media_create_pad_links(mdev,
					     MEDIA_ENT_F_DTV_DEMOD,
					     demod, 1,
					     MEDIA_ENT_F_TS_DEMUX,
					     demux, 0, MEDIA_LNK_FL_ENABLED,
					     false);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (demux && ca) अणु
		ret = media_create_pad_link(demux, 1, ca,
					    0, MEDIA_LNK_FL_ENABLED);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Create demux links क्रम each ringbuffer/pad */
	अगर (demux) अणु
		media_device_क्रम_each_entity(entity, mdev) अणु
			अगर (entity->function == MEDIA_ENT_F_IO_DTV) अणु
				अगर (!म_भेदन(entity->name, DVR_TSOUT,
				    म_माप(DVR_TSOUT))) अणु
					ret = media_create_pad_link(demux,
								++dvr_pad,
							    entity, 0, 0);
					अगर (ret)
						वापस ret;
				पूर्ण
				अगर (!म_भेदन(entity->name, DEMUX_TSOUT,
				    म_माप(DEMUX_TSOUT))) अणु
					ret = media_create_pad_link(demux,
							      ++demux_pad,
							    entity, 0, 0);
					अगर (ret)
						वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Create पूर्णांकerface links क्रम FE->tuner, DVR->demux and CA->ca */
	media_device_क्रम_each_पूर्णांकf(पूर्णांकf, mdev) अणु
		अगर (पूर्णांकf->type == MEDIA_INTF_T_DVB_CA && ca) अणु
			link = media_create_पूर्णांकf_link(ca, पूर्णांकf,
						      MEDIA_LNK_FL_ENABLED |
						      MEDIA_LNK_FL_IMMUTABLE);
			अगर (!link)
				वापस -ENOMEM;
		पूर्ण

		अगर (पूर्णांकf->type == MEDIA_INTF_T_DVB_FE && tuner) अणु
			link = media_create_पूर्णांकf_link(tuner, पूर्णांकf,
						      MEDIA_LNK_FL_ENABLED |
						      MEDIA_LNK_FL_IMMUTABLE);
			अगर (!link)
				वापस -ENOMEM;
		पूर्ण
#अगर 0
		/*
		 * Indirect link - let's not create yet, as we don't know how
		 *		   to handle indirect links, nor अगर this will
		 *		   actually be needed.
		 */
		अगर (पूर्णांकf->type == MEDIA_INTF_T_DVB_DVR && demux) अणु
			link = media_create_पूर्णांकf_link(demux, पूर्णांकf,
						      MEDIA_LNK_FL_ENABLED |
						      MEDIA_LNK_FL_IMMUTABLE);
			अगर (!link)
				वापस -ENOMEM;
		पूर्ण
#पूर्ण_अगर
		अगर (पूर्णांकf->type == MEDIA_INTF_T_DVB_DVR) अणु
			ret = dvb_create_io_पूर्णांकf_links(adap, पूर्णांकf, DVR_TSOUT);
			अगर (ret)
				वापस ret;
		पूर्ण
		अगर (पूर्णांकf->type == MEDIA_INTF_T_DVB_DEMUX) अणु
			ret = dvb_create_io_पूर्णांकf_links(adap, पूर्णांकf, DEMUX_TSOUT);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dvb_create_media_graph);
#पूर्ण_अगर

अटल पूर्णांक dvbdev_check_मुक्त_adapter_num(पूर्णांक num)
अणु
	काष्ठा list_head *entry;
	list_क्रम_each(entry, &dvb_adapter_list) अणु
		काष्ठा dvb_adapter *adap;
		adap = list_entry(entry, काष्ठा dvb_adapter, list_head);
		अगर (adap->num == num)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक dvbdev_get_मुक्त_adapter_num (व्योम)
अणु
	पूर्णांक num = 0;

	जबतक (num < DVB_MAX_ADAPTERS) अणु
		अगर (dvbdev_check_मुक्त_adapter_num(num))
			वापस num;
		num++;
	पूर्ण

	वापस -ENखाता;
पूर्ण


पूर्णांक dvb_रेजिस्टर_adapter(काष्ठा dvb_adapter *adap, स्थिर अक्षर *name,
			 काष्ठा module *module, काष्ठा device *device,
			 लघु *adapter_nums)
अणु
	पूर्णांक i, num;

	mutex_lock(&dvbdev_रेजिस्टर_lock);

	क्रम (i = 0; i < DVB_MAX_ADAPTERS; ++i) अणु
		num = adapter_nums[i];
		अगर (num >= 0  &&  num < DVB_MAX_ADAPTERS) अणु
		/* use the one the driver asked क्रम */
			अगर (dvbdev_check_मुक्त_adapter_num(num))
				अवरोध;
		पूर्ण अन्यथा अणु
			num = dvbdev_get_मुक्त_adapter_num();
			अवरोध;
		पूर्ण
		num = -1;
	पूर्ण

	अगर (num < 0) अणु
		mutex_unlock(&dvbdev_रेजिस्टर_lock);
		वापस -ENखाता;
	पूर्ण

	स_रखो (adap, 0, माप(काष्ठा dvb_adapter));
	INIT_LIST_HEAD (&adap->device_list);

	pr_info("DVB: registering new adapter (%s)\n", name);

	adap->num = num;
	adap->name = name;
	adap->module = module;
	adap->device = device;
	adap->mfe_shared = 0;
	adap->mfe_dvbdev = शून्य;
	mutex_init (&adap->mfe_lock);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	mutex_init(&adap->mdev_lock);
#पूर्ण_अगर

	list_add_tail (&adap->list_head, &dvb_adapter_list);

	mutex_unlock(&dvbdev_रेजिस्टर_lock);

	वापस num;
पूर्ण
EXPORT_SYMBOL(dvb_रेजिस्टर_adapter);


पूर्णांक dvb_unरेजिस्टर_adapter(काष्ठा dvb_adapter *adap)
अणु
	mutex_lock(&dvbdev_रेजिस्टर_lock);
	list_del (&adap->list_head);
	mutex_unlock(&dvbdev_रेजिस्टर_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dvb_unरेजिस्टर_adapter);

/* अगर the miracle happens and "generic_usercopy()" is included पूर्णांकo
   the kernel, then this can vanish. please करोn't make the mistake and
   define this as video_usercopy(). this will पूर्णांकroduce a dependency
   to the v4l "videodev.o" module, which is unnecessary क्रम some
   cards (ie. the budget dvb-cards करोn't need the v4l module...) */
पूर्णांक dvb_usercopy(काष्ठा file *file,
		     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
		     पूर्णांक (*func)(काष्ठा file *file,
		     अचिन्हित पूर्णांक cmd, व्योम *arg))
अणु
	अक्षर    sbuf[128];
	व्योम    *mbuf = शून्य;
	व्योम    *parg = शून्य;
	पूर्णांक     err  = -EINVAL;

	/*  Copy arguments पूर्णांकo temp kernel buffer  */
	चयन (_IOC_सूची(cmd)) अणु
	हाल _IOC_NONE:
		/*
		 * For this command, the poपूर्णांकer is actually an पूर्णांकeger
		 * argument.
		 */
		parg = (व्योम *) arg;
		अवरोध;
	हाल _IOC_READ: /* some v4l ioctls are marked wrong ... */
	हाल _IOC_WRITE:
	हाल (_IOC_WRITE | _IOC_READ):
		अगर (_IOC_SIZE(cmd) <= माप(sbuf)) अणु
			parg = sbuf;
		पूर्ण अन्यथा अणु
			/* too big to allocate from stack */
			mbuf = kदो_स्मृति(_IOC_SIZE(cmd), GFP_KERNEL);
			अगर (शून्य == mbuf)
				वापस -ENOMEM;
			parg = mbuf;
		पूर्ण

		err = -EFAULT;
		अगर (copy_from_user(parg, (व्योम __user *)arg, _IOC_SIZE(cmd)))
			जाओ out;
		अवरोध;
	पूर्ण

	/* call driver */
	अगर ((err = func(file, cmd, parg)) == -ENOIOCTLCMD)
		err = -ENOTTY;

	अगर (err < 0)
		जाओ out;

	/*  Copy results पूर्णांकo user buffer  */
	चयन (_IOC_सूची(cmd))
	अणु
	हाल _IOC_READ:
	हाल (_IOC_WRITE | _IOC_READ):
		अगर (copy_to_user((व्योम __user *)arg, parg, _IOC_SIZE(cmd)))
			err = -EFAULT;
		अवरोध;
	पूर्ण

out:
	kमुक्त(mbuf);
	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_I2C)
काष्ठा i2c_client *dvb_module_probe(स्थिर अक्षर *module_name,
				    स्थिर अक्षर *name,
				    काष्ठा i2c_adapter *adap,
				    अचिन्हित अक्षर addr,
				    व्योम *platक्रमm_data)
अणु
	काष्ठा i2c_client *client;
	काष्ठा i2c_board_info *board_info;

	board_info = kzalloc(माप(*board_info), GFP_KERNEL);
	अगर (!board_info)
		वापस शून्य;

	अगर (name)
		strscpy(board_info->type, name, I2C_NAME_SIZE);
	अन्यथा
		strscpy(board_info->type, module_name, I2C_NAME_SIZE);

	board_info->addr = addr;
	board_info->platक्रमm_data = platक्रमm_data;
	request_module(module_name);
	client = i2c_new_client_device(adap, board_info);
	अगर (!i2c_client_has_driver(client)) अणु
		kमुक्त(board_info);
		वापस शून्य;
	पूर्ण

	अगर (!try_module_get(client->dev.driver->owner)) अणु
		i2c_unरेजिस्टर_device(client);
		client = शून्य;
	पूर्ण

	kमुक्त(board_info);
	वापस client;
पूर्ण
EXPORT_SYMBOL_GPL(dvb_module_probe);

व्योम dvb_module_release(काष्ठा i2c_client *client)
अणु
	अगर (!client)
		वापस;

	module_put(client->dev.driver->owner);
	i2c_unरेजिस्टर_device(client);
पूर्ण
EXPORT_SYMBOL_GPL(dvb_module_release);
#पूर्ण_अगर

अटल पूर्णांक dvb_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा dvb_device *dvbdev = dev_get_drvdata(dev);

	add_uevent_var(env, "DVB_ADAPTER_NUM=%d", dvbdev->adapter->num);
	add_uevent_var(env, "DVB_DEVICE_TYPE=%s", dnames[dvbdev->type]);
	add_uevent_var(env, "DVB_DEVICE_NUM=%d", dvbdev->id);
	वापस 0;
पूर्ण

अटल अक्षर *dvb_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	काष्ठा dvb_device *dvbdev = dev_get_drvdata(dev);

	वापस kaप्र_लिखो(GFP_KERNEL, "dvb/adapter%d/%s%d",
		dvbdev->adapter->num, dnames[dvbdev->type], dvbdev->id);
पूर्ण


अटल पूर्णांक __init init_dvbdev(व्योम)
अणु
	पूर्णांक retval;
	dev_t dev = MKDEV(DVB_MAJOR, 0);

	अगर ((retval = रेजिस्टर_chrdev_region(dev, MAX_DVB_MINORS, "DVB")) != 0) अणु
		pr_err("dvb-core: unable to get major %d\n", DVB_MAJOR);
		वापस retval;
	पूर्ण

	cdev_init(&dvb_device_cdev, &dvb_device_fops);
	अगर ((retval = cdev_add(&dvb_device_cdev, dev, MAX_DVB_MINORS)) != 0) अणु
		pr_err("dvb-core: unable register character device\n");
		जाओ error;
	पूर्ण

	dvb_class = class_create(THIS_MODULE, "dvb");
	अगर (IS_ERR(dvb_class)) अणु
		retval = PTR_ERR(dvb_class);
		जाओ error;
	पूर्ण
	dvb_class->dev_uevent = dvb_uevent;
	dvb_class->devnode = dvb_devnode;
	वापस 0;

error:
	cdev_del(&dvb_device_cdev);
	unरेजिस्टर_chrdev_region(dev, MAX_DVB_MINORS);
	वापस retval;
पूर्ण


अटल व्योम __निकास निकास_dvbdev(व्योम)
अणु
	class_destroy(dvb_class);
	cdev_del(&dvb_device_cdev);
	unरेजिस्टर_chrdev_region(MKDEV(DVB_MAJOR, 0), MAX_DVB_MINORS);
पूर्ण

subsys_initcall(init_dvbdev);
module_निकास(निकास_dvbdev);

MODULE_DESCRIPTION("DVB Core Driver");
MODULE_AUTHOR("Marcus Metzler, Ralph Metzler, Holger Waechtler");
MODULE_LICENSE("GPL");
