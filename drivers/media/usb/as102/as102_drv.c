<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 * Copyright (C) 2010 Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/kref.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>

/* header file क्रम usb device driver*/
#समावेश "as102_drv.h"
#समावेश "as10x_cmd.h"
#समावेश "as102_fe.h"
#समावेश "as102_fw.h"
#समावेश <media/dvbdev.h>

पूर्णांक dual_tuner;
module_param_named(dual_tuner, dual_tuner, पूर्णांक, 0644);
MODULE_PARM_DESC(dual_tuner, "Activate Dual-Tuner config (default: off)");

अटल पूर्णांक fw_upload = 1;
module_param_named(fw_upload, fw_upload, पूर्णांक, 0644);
MODULE_PARM_DESC(fw_upload, "Turn on/off default FW upload (default: on)");

अटल पूर्णांक pid_filtering;
module_param_named(pid_filtering, pid_filtering, पूर्णांक, 0644);
MODULE_PARM_DESC(pid_filtering, "Activate HW PID filtering (default: off)");

अटल पूर्णांक ts_स्वतः_disable;
module_param_named(ts_स्वतः_disable, ts_स्वतः_disable, पूर्णांक, 0644);
MODULE_PARM_DESC(ts_स्वतः_disable, "Stream Auto Enable on FW (default: off)");

पूर्णांक elna_enable = 1;
module_param_named(elna_enable, elna_enable, पूर्णांक, 0644);
MODULE_PARM_DESC(elna_enable, "Activate eLNA (default: on)");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल व्योम as102_stop_stream(काष्ठा as102_dev_t *dev)
अणु
	काष्ठा as10x_bus_adapter_t *bus_adap;

	अगर (dev != शून्य)
		bus_adap = &dev->bus_adap;
	अन्यथा
		वापस;

	अगर (bus_adap->ops->stop_stream != शून्य)
		bus_adap->ops->stop_stream(dev);

	अगर (ts_स्वतः_disable) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&dev->bus_adap.lock))
			वापस;

		अगर (as10x_cmd_stop_streaming(bus_adap) < 0)
			dev_dbg(&dev->bus_adap.usb_dev->dev,
				"as10x_cmd_stop_streaming failed\n");

		mutex_unlock(&dev->bus_adap.lock);
	पूर्ण
पूर्ण

अटल पूर्णांक as102_start_stream(काष्ठा as102_dev_t *dev)
अणु
	काष्ठा as10x_bus_adapter_t *bus_adap;
	पूर्णांक ret = -EFAULT;

	अगर (dev != शून्य)
		bus_adap = &dev->bus_adap;
	अन्यथा
		वापस ret;

	अगर (bus_adap->ops->start_stream != शून्य)
		ret = bus_adap->ops->start_stream(dev);

	अगर (ts_स्वतः_disable) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&dev->bus_adap.lock))
			वापस -EFAULT;

		ret = as10x_cmd_start_streaming(bus_adap);

		mutex_unlock(&dev->bus_adap.lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक as10x_pid_filter(काष्ठा as102_dev_t *dev,
			    पूर्णांक index, u16 pid, पूर्णांक onoff) अणु

	काष्ठा as10x_bus_adapter_t *bus_adap = &dev->bus_adap;
	पूर्णांक ret = -EFAULT;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->bus_adap.lock)) अणु
		dev_dbg(&dev->bus_adap.usb_dev->dev,
			"amutex_lock_interruptible(lock) failed !\n");
		वापस -EBUSY;
	पूर्ण

	चयन (onoff) अणु
	हाल 0:
		ret = as10x_cmd_del_PID_filter(bus_adap, (uपूर्णांक16_t) pid);
		dev_dbg(&dev->bus_adap.usb_dev->dev,
			"DEL_PID_FILTER([%02d] 0x%04x) ret = %d\n",
			index, pid, ret);
		अवरोध;
	हाल 1:
	अणु
		काष्ठा as10x_ts_filter filter;

		filter.type = TS_PID_TYPE_TS;
		filter.idx = 0xFF;
		filter.pid = pid;

		ret = as10x_cmd_add_PID_filter(bus_adap, &filter);
		dev_dbg(&dev->bus_adap.usb_dev->dev,
			"ADD_PID_FILTER([%02d -> %02d], 0x%04x) ret = %d\n",
			index, filter.idx, filter.pid, ret);
		अवरोध;
	पूर्ण
	पूर्ण

	mutex_unlock(&dev->bus_adap.lock);
	वापस ret;
पूर्ण

अटल पूर्णांक as102_dvb_dmx_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	पूर्णांक ret = 0;
	काष्ठा dvb_demux *demux = dvbdmxfeed->demux;
	काष्ठा as102_dev_t *as102_dev = demux->priv;

	अगर (mutex_lock_पूर्णांकerruptible(&as102_dev->sem))
		वापस -ERESTARTSYS;

	अगर (pid_filtering)
		as10x_pid_filter(as102_dev, dvbdmxfeed->index,
				 dvbdmxfeed->pid, 1);

	अगर (as102_dev->streaming++ == 0)
		ret = as102_start_stream(as102_dev);

	mutex_unlock(&as102_dev->sem);
	वापस ret;
पूर्ण

अटल पूर्णांक as102_dvb_dmx_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *demux = dvbdmxfeed->demux;
	काष्ठा as102_dev_t *as102_dev = demux->priv;

	अगर (mutex_lock_पूर्णांकerruptible(&as102_dev->sem))
		वापस -ERESTARTSYS;

	अगर (--as102_dev->streaming == 0)
		as102_stop_stream(as102_dev);

	अगर (pid_filtering)
		as10x_pid_filter(as102_dev, dvbdmxfeed->index,
				 dvbdmxfeed->pid, 0);

	mutex_unlock(&as102_dev->sem);
	वापस 0;
पूर्ण

अटल पूर्णांक as102_set_tune(व्योम *priv, काष्ठा as10x_tune_args *tune_args)
अणु
	काष्ठा as10x_bus_adapter_t *bus_adap = priv;
	पूर्णांक ret;

	/* Set frontend arguments */
	अगर (mutex_lock_पूर्णांकerruptible(&bus_adap->lock))
		वापस -EBUSY;

	ret =  as10x_cmd_set_tune(bus_adap, tune_args);
	अगर (ret != 0)
		dev_dbg(&bus_adap->usb_dev->dev,
			"as10x_cmd_set_tune failed. (err = %d)\n", ret);

	mutex_unlock(&bus_adap->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक as102_get_tps(व्योम *priv, काष्ठा as10x_tps *tps)
अणु
	काष्ठा as10x_bus_adapter_t *bus_adap = priv;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&bus_adap->lock))
		वापस -EBUSY;

	/* send abilis command: GET_TPS */
	ret = as10x_cmd_get_tps(bus_adap, tps);

	mutex_unlock(&bus_adap->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक as102_get_status(व्योम *priv, काष्ठा as10x_tune_status *tstate)
अणु
	काष्ठा as10x_bus_adapter_t *bus_adap = priv;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&bus_adap->lock))
		वापस -EBUSY;

	/* send abilis command: GET_TUNE_STATUS */
	ret = as10x_cmd_get_tune_status(bus_adap, tstate);
	अगर (ret < 0) अणु
		dev_dbg(&bus_adap->usb_dev->dev,
			"as10x_cmd_get_tune_status failed (err = %d)\n",
			ret);
	पूर्ण

	mutex_unlock(&bus_adap->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक as102_get_stats(व्योम *priv, काष्ठा as10x_demod_stats *demod_stats)
अणु
	काष्ठा as10x_bus_adapter_t *bus_adap = priv;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&bus_adap->lock))
		वापस -EBUSY;

	/* send abilis command: GET_TUNE_STATUS */
	ret = as10x_cmd_get_demod_stats(bus_adap, demod_stats);
	अगर (ret < 0) अणु
		dev_dbg(&bus_adap->usb_dev->dev,
			"as10x_cmd_get_demod_stats failed (probably not tuned)\n");
	पूर्ण अन्यथा अणु
		dev_dbg(&bus_adap->usb_dev->dev,
			"demod status: fc: 0x%08x, bad fc: 0x%08x, bytes corrected: 0x%08x , MER: 0x%04x\n",
			demod_stats->frame_count,
			demod_stats->bad_frame_count,
			demod_stats->bytes_fixed_by_rs,
			demod_stats->mer);
	पूर्ण
	mutex_unlock(&bus_adap->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक as102_stream_ctrl(व्योम *priv, पूर्णांक acquire, uपूर्णांक32_t elna_cfg)
अणु
	काष्ठा as10x_bus_adapter_t *bus_adap = priv;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&bus_adap->lock))
		वापस -EBUSY;

	अगर (acquire) अणु
		अगर (elna_enable)
			as10x_cmd_set_context(bus_adap,
					      CONTEXT_LNA, elna_cfg);

		ret = as10x_cmd_turn_on(bus_adap);
	पूर्ण अन्यथा अणु
		ret = as10x_cmd_turn_off(bus_adap);
	पूर्ण

	mutex_unlock(&bus_adap->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा as102_fe_ops as102_fe_ops = अणु
	.set_tune = as102_set_tune,
	.get_tps  = as102_get_tps,
	.get_status = as102_get_status,
	.get_stats = as102_get_stats,
	.stream_ctrl = as102_stream_ctrl,
पूर्ण;

पूर्णांक as102_dvb_रेजिस्टर(काष्ठा as102_dev_t *as102_dev)
अणु
	काष्ठा device *dev = &as102_dev->bus_adap.usb_dev->dev;
	पूर्णांक ret;

	ret = dvb_रेजिस्टर_adapter(&as102_dev->dvb_adap,
			   as102_dev->name, THIS_MODULE,
			   dev, adapter_nr);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: dvb_register_adapter() failed: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	as102_dev->dvb_dmx.priv = as102_dev;
	as102_dev->dvb_dmx.filternum = pid_filtering ? 16 : 256;
	as102_dev->dvb_dmx.feednum = 256;
	as102_dev->dvb_dmx.start_feed = as102_dvb_dmx_start_feed;
	as102_dev->dvb_dmx.stop_feed = as102_dvb_dmx_stop_feed;

	as102_dev->dvb_dmx.dmx.capabilities = DMX_TS_FILTERING |
					      DMX_SECTION_FILTERING;

	as102_dev->dvb_dmxdev.filternum = as102_dev->dvb_dmx.filternum;
	as102_dev->dvb_dmxdev.demux = &as102_dev->dvb_dmx.dmx;
	as102_dev->dvb_dmxdev.capabilities = 0;

	ret = dvb_dmx_init(&as102_dev->dvb_dmx);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: dvb_dmx_init() failed: %d\n", __func__, ret);
		जाओ edmxinit;
	पूर्ण

	ret = dvb_dmxdev_init(&as102_dev->dvb_dmxdev, &as102_dev->dvb_adap);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: dvb_dmxdev_init() failed: %d\n",
			__func__, ret);
		जाओ edmxdinit;
	पूर्ण

	/* Attach the frontend */
	as102_dev->dvb_fe = dvb_attach(as102_attach, as102_dev->name,
				       &as102_fe_ops,
				       &as102_dev->bus_adap,
				       as102_dev->elna_cfg);
	अगर (!as102_dev->dvb_fe) अणु
		ret = -ENODEV;
		dev_err(dev, "%s: as102_attach() failed: %d",
		    __func__, ret);
		जाओ efereg;
	पूर्ण

	ret =  dvb_रेजिस्टर_frontend(&as102_dev->dvb_adap, as102_dev->dvb_fe);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: as102_dvb_register_frontend() failed: %d",
		    __func__, ret);
		जाओ efereg;
	पूर्ण

	/* init bus mutex क्रम token locking */
	mutex_init(&as102_dev->bus_adap.lock);

	/* init start / stop stream mutex */
	mutex_init(&as102_dev->sem);

	/*
	 * try to load as102 firmware. If firmware upload failed, we'll be
	 * able to upload it later.
	 */
	अगर (fw_upload)
		try_then_request_module(as102_fw_upload(&as102_dev->bus_adap),
				"firmware_class");

	pr_info("Registered device %s", as102_dev->name);
	वापस 0;

efereg:
	dvb_dmxdev_release(&as102_dev->dvb_dmxdev);
edmxdinit:
	dvb_dmx_release(&as102_dev->dvb_dmx);
edmxinit:
	dvb_unरेजिस्टर_adapter(&as102_dev->dvb_adap);
	वापस ret;
पूर्ण

व्योम as102_dvb_unरेजिस्टर(काष्ठा as102_dev_t *as102_dev)
अणु
	/* unरेजिस्टर as102 frontend */
	dvb_unरेजिस्टर_frontend(as102_dev->dvb_fe);

	/* detach frontend */
	dvb_frontend_detach(as102_dev->dvb_fe);

	/* unरेजिस्टर demux device */
	dvb_dmxdev_release(&as102_dev->dvb_dmxdev);
	dvb_dmx_release(&as102_dev->dvb_dmx);

	/* unरेजिस्टर dvb adapter */
	dvb_unरेजिस्टर_adapter(&as102_dev->dvb_adap);

	pr_info("Unregistered device %s", as102_dev->name);
पूर्ण

module_usb_driver(as102_usb_driver);

/* modinfo details */
MODULE_DESCRIPTION(DRIVER_FULL_NAME);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pierrick Hascoet <pierrick.hascoet@abilis.com>");
