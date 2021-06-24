<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * some helper function क्रम simple DVB cards which simply DMA the
 * complete transport stream and let the computer sort everything अन्यथा
 * (i.e. we are using the software demux, ...).  Also uses the
 * video-buf to manage DMA buffers.
 *
 * (c) 2004 Gerd Knorr <kraxel@bytesex.org> [SUSE Lअसल]
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>

#समावेश <media/videobuf2-dvb.h>

/* ------------------------------------------------------------------ */

MODULE_AUTHOR("Gerd Knorr <kraxel@bytesex.org> [SuSE Labs]");
MODULE_LICENSE("GPL");

/* ------------------------------------------------------------------ */

अटल पूर्णांक dvb_fnc(काष्ठा vb2_buffer *vb, व्योम *priv)
अणु
	काष्ठा vb2_dvb *dvb = priv;

	dvb_dmx_swfilter(&dvb->demux, vb2_plane_vaddr(vb, 0),
				      vb2_get_plane_payload(vb, 0));
	वापस 0;
पूर्ण

अटल पूर्णांक vb2_dvb_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा vb2_dvb *dvb = demux->priv;
	पूर्णांक rc = 0;

	अगर (!demux->dmx.frontend)
		वापस -EINVAL;

	mutex_lock(&dvb->lock);
	dvb->nfeeds++;

	अगर (!dvb->dvbq.thपढ़ोio) अणु
		rc = vb2_thपढ़ो_start(&dvb->dvbq, dvb_fnc, dvb, dvb->name);
		अगर (rc)
			dvb->nfeeds--;
	पूर्ण
	अगर (!rc)
		rc = dvb->nfeeds;
	mutex_unlock(&dvb->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक vb2_dvb_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा vb2_dvb *dvb = demux->priv;
	पूर्णांक err = 0;

	mutex_lock(&dvb->lock);
	dvb->nfeeds--;
	अगर (0 == dvb->nfeeds)
		err = vb2_thपढ़ो_stop(&dvb->dvbq);
	mutex_unlock(&dvb->lock);
	वापस err;
पूर्ण

अटल पूर्णांक vb2_dvb_रेजिस्टर_adapter(काष्ठा vb2_dvb_frontends *fe,
			  काष्ठा module *module,
			  व्योम *adapter_priv,
			  काष्ठा device *device,
			  काष्ठा media_device *mdev,
			  अक्षर *adapter_name,
			  लघु *adapter_nr,
			  पूर्णांक mfe_shared)
अणु
	पूर्णांक result;

	mutex_init(&fe->lock);

	/* रेजिस्टर adapter */
	result = dvb_रेजिस्टर_adapter(&fe->adapter, adapter_name, module,
		device, adapter_nr);
	अगर (result < 0) अणु
		pr_warn("%s: dvb_register_adapter failed (errno = %d)\n",
		       adapter_name, result);
	पूर्ण
	fe->adapter.priv = adapter_priv;
	fe->adapter.mfe_shared = mfe_shared;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	अगर (mdev)
		fe->adapter.mdev = mdev;
#पूर्ण_अगर
	वापस result;
पूर्ण

अटल पूर्णांक vb2_dvb_रेजिस्टर_frontend(काष्ठा dvb_adapter *adapter,
	काष्ठा vb2_dvb *dvb)
अणु
	पूर्णांक result;

	/* रेजिस्टर frontend */
	result = dvb_रेजिस्टर_frontend(adapter, dvb->frontend);
	अगर (result < 0) अणु
		pr_warn("%s: dvb_register_frontend failed (errno = %d)\n",
		       dvb->name, result);
		जाओ fail_frontend;
	पूर्ण

	/* रेजिस्टर demux stuff */
	dvb->demux.dmx.capabilities =
		DMX_TS_FILTERING | DMX_SECTION_FILTERING |
		DMX_MEMORY_BASED_FILTERING;
	dvb->demux.priv       = dvb;
	dvb->demux.filternum  = 256;
	dvb->demux.feednum    = 256;
	dvb->demux.start_feed = vb2_dvb_start_feed;
	dvb->demux.stop_feed  = vb2_dvb_stop_feed;
	result = dvb_dmx_init(&dvb->demux);
	अगर (result < 0) अणु
		pr_warn("%s: dvb_dmx_init failed (errno = %d)\n",
		       dvb->name, result);
		जाओ fail_dmx;
	पूर्ण

	dvb->dmxdev.filternum    = 256;
	dvb->dmxdev.demux        = &dvb->demux.dmx;
	dvb->dmxdev.capabilities = 0;
	result = dvb_dmxdev_init(&dvb->dmxdev, adapter);

	अगर (result < 0) अणु
		pr_warn("%s: dvb_dmxdev_init failed (errno = %d)\n",
		       dvb->name, result);
		जाओ fail_dmxdev;
	पूर्ण

	dvb->fe_hw.source = DMX_FRONTEND_0;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	अगर (result < 0) अणु
		pr_warn("%s: add_frontend failed (DMX_FRONTEND_0, errno = %d)\n",
		       dvb->name, result);
		जाओ fail_fe_hw;
	पूर्ण

	dvb->fe_mem.source = DMX_MEMORY_FE;
	result = dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->fe_mem);
	अगर (result < 0) अणु
		pr_warn("%s: add_frontend failed (DMX_MEMORY_FE, errno = %d)\n",
		       dvb->name, result);
		जाओ fail_fe_mem;
	पूर्ण

	result = dvb->demux.dmx.connect_frontend(&dvb->demux.dmx, &dvb->fe_hw);
	अगर (result < 0) अणु
		pr_warn("%s: connect_frontend failed (errno = %d)\n",
		       dvb->name, result);
		जाओ fail_fe_conn;
	पूर्ण

	/* रेजिस्टर network adapter */
	result = dvb_net_init(adapter, &dvb->net, &dvb->demux.dmx);
	अगर (result < 0) अणु
		pr_warn("%s: dvb_net_init failed (errno = %d)\n",
		       dvb->name, result);
		जाओ fail_fe_conn;
	पूर्ण
	वापस 0;

fail_fe_conn:
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_mem);
fail_fe_mem:
	dvb->demux.dmx.हटाओ_frontend(&dvb->demux.dmx, &dvb->fe_hw);
fail_fe_hw:
	dvb_dmxdev_release(&dvb->dmxdev);
fail_dmxdev:
	dvb_dmx_release(&dvb->demux);
fail_dmx:
	dvb_unरेजिस्टर_frontend(dvb->frontend);
fail_frontend:
	dvb_frontend_detach(dvb->frontend);
	dvb->frontend = शून्य;

	वापस result;
पूर्ण

/* ------------------------------------------------------------------ */
/* Register a single adapter and one or more frontends */
पूर्णांक vb2_dvb_रेजिस्टर_bus(काष्ठा vb2_dvb_frontends *f,
			 काष्ठा module *module,
			 व्योम *adapter_priv,
			 काष्ठा device *device,
			 काष्ठा media_device *mdev,
			 लघु *adapter_nr,
			 पूर्णांक mfe_shared)
अणु
	काष्ठा list_head *list, *q;
	काष्ठा vb2_dvb_frontend *fe;
	पूर्णांक res;

	fe = vb2_dvb_get_frontend(f, 1);
	अगर (!fe) अणु
		pr_warn("Unable to register the adapter which has no frontends\n");
		वापस -EINVAL;
	पूर्ण

	/* Bring up the adapter */
	res = vb2_dvb_रेजिस्टर_adapter(f, module, adapter_priv, device, mdev,
		fe->dvb.name, adapter_nr, mfe_shared);
	अगर (res < 0) अणु
		pr_warn("vb2_dvb_register_adapter failed (errno = %d)\n", res);
		वापस res;
	पूर्ण

	/* Attach all of the frontends to the adapter */
	mutex_lock(&f->lock);
	list_क्रम_each_safe(list, q, &f->felist) अणु
		fe = list_entry(list, काष्ठा vb2_dvb_frontend, felist);
		res = vb2_dvb_रेजिस्टर_frontend(&f->adapter, &fe->dvb);
		अगर (res < 0) अणु
			pr_warn("%s: vb2_dvb_register_frontend failed (errno = %d)\n",
				fe->dvb.name, res);
			जाओ err;
		पूर्ण
		res = dvb_create_media_graph(&f->adapter, false);
		अगर (res < 0)
			जाओ err;
	पूर्ण

	mutex_unlock(&f->lock);
	वापस 0;

err:
	mutex_unlock(&f->lock);
	vb2_dvb_unरेजिस्टर_bus(f);
	वापस res;
पूर्ण
EXPORT_SYMBOL(vb2_dvb_रेजिस्टर_bus);

व्योम vb2_dvb_unरेजिस्टर_bus(काष्ठा vb2_dvb_frontends *f)
अणु
	vb2_dvb_dealloc_frontends(f);

	dvb_unरेजिस्टर_adapter(&f->adapter);
पूर्ण
EXPORT_SYMBOL(vb2_dvb_unरेजिस्टर_bus);

काष्ठा vb2_dvb_frontend *vb2_dvb_get_frontend(
	काष्ठा vb2_dvb_frontends *f, पूर्णांक id)
अणु
	काष्ठा list_head *list, *q;
	काष्ठा vb2_dvb_frontend *fe, *ret = शून्य;

	mutex_lock(&f->lock);

	list_क्रम_each_safe(list, q, &f->felist) अणु
		fe = list_entry(list, काष्ठा vb2_dvb_frontend, felist);
		अगर (fe->id == id) अणु
			ret = fe;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&f->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vb2_dvb_get_frontend);

पूर्णांक vb2_dvb_find_frontend(काष्ठा vb2_dvb_frontends *f,
	काष्ठा dvb_frontend *p)
अणु
	काष्ठा list_head *list, *q;
	काष्ठा vb2_dvb_frontend *fe = शून्य;
	पूर्णांक ret = 0;

	mutex_lock(&f->lock);

	list_क्रम_each_safe(list, q, &f->felist) अणु
		fe = list_entry(list, काष्ठा vb2_dvb_frontend, felist);
		अगर (fe->dvb.frontend == p) अणु
			ret = fe->id;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&f->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vb2_dvb_find_frontend);

काष्ठा vb2_dvb_frontend *vb2_dvb_alloc_frontend(
	काष्ठा vb2_dvb_frontends *f, पूर्णांक id)
अणु
	काष्ठा vb2_dvb_frontend *fe;

	fe = kzalloc(माप(काष्ठा vb2_dvb_frontend), GFP_KERNEL);
	अगर (fe == शून्य)
		वापस शून्य;

	fe->id = id;
	mutex_init(&fe->dvb.lock);

	mutex_lock(&f->lock);
	list_add_tail(&fe->felist, &f->felist);
	mutex_unlock(&f->lock);
	वापस fe;
पूर्ण
EXPORT_SYMBOL(vb2_dvb_alloc_frontend);

व्योम vb2_dvb_dealloc_frontends(काष्ठा vb2_dvb_frontends *f)
अणु
	काष्ठा list_head *list, *q;
	काष्ठा vb2_dvb_frontend *fe;

	mutex_lock(&f->lock);
	list_क्रम_each_safe(list, q, &f->felist) अणु
		fe = list_entry(list, काष्ठा vb2_dvb_frontend, felist);
		अगर (fe->dvb.net.dvbdev) अणु
			dvb_net_release(&fe->dvb.net);
			fe->dvb.demux.dmx.हटाओ_frontend(&fe->dvb.demux.dmx,
				&fe->dvb.fe_mem);
			fe->dvb.demux.dmx.हटाओ_frontend(&fe->dvb.demux.dmx,
				&fe->dvb.fe_hw);
			dvb_dmxdev_release(&fe->dvb.dmxdev);
			dvb_dmx_release(&fe->dvb.demux);
			dvb_unरेजिस्टर_frontend(fe->dvb.frontend);
		पूर्ण
		अगर (fe->dvb.frontend)
			/* always allocated, may have been reset */
			dvb_frontend_detach(fe->dvb.frontend);
		list_del(list); /* हटाओ list entry */
		kमुक्त(fe);	/* मुक्त frontend allocation */
	पूर्ण
	mutex_unlock(&f->lock);
पूर्ण
EXPORT_SYMBOL(vb2_dvb_dealloc_frontends);
