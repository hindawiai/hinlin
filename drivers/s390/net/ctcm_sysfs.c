<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2007, 2007
 * Authors:	Peter Tiedemann (ptiedem@de.ibm.com)
 *
 */

#अघोषित DEBUG
#अघोषित DEBUGDATA
#अघोषित DEBUGCCW

#घोषणा KMSG_COMPONENT "ctcm"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>
#समावेश "ctcm_main.h"

/*
 * sysfs attributes
 */

अटल sमाप_प्रकार ctcm_buffer_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctcm_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n", priv->buffer_size);
पूर्ण

अटल sमाप_प्रकार ctcm_buffer_ग_लिखो(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा net_device *ndev;
	अचिन्हित पूर्णांक bs1;
	काष्ठा ctcm_priv *priv = dev_get_drvdata(dev);
	पूर्णांक rc;

	ndev = priv->channel[CTCM_READ]->netdev;
	अगर (!(priv && priv->channel[CTCM_READ] && ndev)) अणु
		CTCM_DBF_TEXT(SETUP, CTC_DBF_ERROR, "bfnondev");
		वापस -ENODEV;
	पूर्ण

	rc = kstrtouपूर्णांक(buf, 0, &bs1);
	अगर (rc)
		जाओ einval;
	अगर (bs1 > CTCM_बफ_मानE_LIMIT)
					जाओ einval;
	अगर (bs1 < (576 + LL_HEADER_LENGTH + 2))
					जाओ einval;
	priv->buffer_size = bs1;	/* just to overग_लिखो the शेष */

	अगर ((ndev->flags & IFF_RUNNING) &&
	    (bs1 < (ndev->mtu + LL_HEADER_LENGTH + 2)))
					जाओ einval;

	priv->channel[CTCM_READ]->max_bufsize = bs1;
	priv->channel[CTCM_WRITE]->max_bufsize = bs1;
	अगर (!(ndev->flags & IFF_RUNNING))
		ndev->mtu = bs1 - LL_HEADER_LENGTH - 2;
	priv->channel[CTCM_READ]->flags |= CHANNEL_FLAGS_बफ_मानE_CHANGED;
	priv->channel[CTCM_WRITE]->flags |= CHANNEL_FLAGS_बफ_मानE_CHANGED;

	CTCM_DBF_DEV(SETUP, ndev, buf);
	वापस count;

einval:
	CTCM_DBF_DEV(SETUP, ndev, "buff_err");
	वापस -EINVAL;
पूर्ण

अटल व्योम ctcm_prपूर्णांक_statistics(काष्ठा ctcm_priv *priv)
अणु
	अक्षर *sbuf;
	अक्षर *p;

	अगर (!priv)
		वापस;
	sbuf = kदो_स्मृति(2048, GFP_KERNEL);
	अगर (sbuf == शून्य)
		वापस;
	p = sbuf;

	p += प्र_लिखो(p, "  Device FSM state: %s\n",
		     fsm_माला_लोtate_str(priv->fsm));
	p += प्र_लिखो(p, "  RX channel FSM state: %s\n",
		     fsm_माला_लोtate_str(priv->channel[CTCM_READ]->fsm));
	p += प्र_लिखो(p, "  TX channel FSM state: %s\n",
		     fsm_माला_लोtate_str(priv->channel[CTCM_WRITE]->fsm));
	p += प्र_लिखो(p, "  Max. TX buffer used: %ld\n",
		     priv->channel[WRITE]->prof.maxmulti);
	p += प्र_लिखो(p, "  Max. chained SKBs: %ld\n",
		     priv->channel[WRITE]->prof.maxcqueue);
	p += प्र_लिखो(p, "  TX single write ops: %ld\n",
		     priv->channel[WRITE]->prof.करोios_single);
	p += प्र_लिखो(p, "  TX multi write ops: %ld\n",
		     priv->channel[WRITE]->prof.करोios_multi);
	p += प्र_लिखो(p, "  Netto bytes written: %ld\n",
		     priv->channel[WRITE]->prof.txlen);
	p += प्र_लिखो(p, "  Max. TX IO-time: %u\n",
		     jअगरfies_to_usecs(priv->channel[WRITE]->prof.tx_समय));

	prपूर्णांकk(KERN_INFO "Statistics for %s:\n%s",
				priv->channel[CTCM_WRITE]->netdev->name, sbuf);
	kमुक्त(sbuf);
	वापस;
पूर्ण

अटल sमाप_प्रकार stats_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ccwgroup_device *gdev = to_ccwgroupdev(dev);
	काष्ठा ctcm_priv *priv = dev_get_drvdata(dev);

	अगर (!priv || gdev->state != CCWGROUP_ONLINE)
		वापस -ENODEV;
	ctcm_prपूर्णांक_statistics(priv);
	वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार stats_ग_लिखो(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ctcm_priv *priv = dev_get_drvdata(dev);
	अगर (!priv)
		वापस -ENODEV;
	/* Reset statistics */
	स_रखो(&priv->channel[WRITE]->prof, 0,
				माप(priv->channel[CTCM_WRITE]->prof));
	वापस count;
पूर्ण

अटल sमाप_प्रकार ctcm_proto_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ctcm_priv *priv = dev_get_drvdata(dev);
	अगर (!priv)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%d\n", priv->protocol);
पूर्ण

अटल sमाप_प्रकार ctcm_proto_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक value, rc;
	काष्ठा ctcm_priv *priv = dev_get_drvdata(dev);

	अगर (!priv)
		वापस -ENODEV;
	rc = kstrtoपूर्णांक(buf, 0, &value);
	अगर (rc ||
	    !((value == CTCM_PROTO_S390)  ||
	      (value == CTCM_PROTO_LINUX) ||
	      (value == CTCM_PROTO_MPC) ||
	      (value == CTCM_PROTO_OS390)))
		वापस -EINVAL;
	priv->protocol = value;
	CTCM_DBF_DEV(SETUP, dev, buf);

	वापस count;
पूर्ण

अटल स्थिर अक्षर *ctcm_type[] = अणु
	"not a channel",
	"CTC/A",
	"FICON channel",
	"ESCON channel",
	"unknown channel type",
	"unsupported channel type",
पूर्ण;

अटल sमाप_प्रकार ctcm_type_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ccwgroup_device *cgdev;

	cgdev = to_ccwgroupdev(dev);
	अगर (!cgdev)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%s\n",
			ctcm_type[cgdev->cdev[0]->id.driver_info]);
पूर्ण

अटल DEVICE_ATTR(buffer, 0644, ctcm_buffer_show, ctcm_buffer_ग_लिखो);
अटल DEVICE_ATTR(protocol, 0644, ctcm_proto_show, ctcm_proto_store);
अटल DEVICE_ATTR(type, 0444, ctcm_type_show, शून्य);
अटल DEVICE_ATTR(stats, 0644, stats_show, stats_ग_लिखो);

अटल काष्ठा attribute *ctcm_attr[] = अणु
	&dev_attr_protocol.attr,
	&dev_attr_type.attr,
	&dev_attr_buffer.attr,
	&dev_attr_stats.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group ctcm_attr_group = अणु
	.attrs = ctcm_attr,
पूर्ण;
स्थिर काष्ठा attribute_group *ctcm_attr_groups[] = अणु
	&ctcm_attr_group,
	शून्य,
पूर्ण;
