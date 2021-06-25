<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  libahci.c - Common AHCI SATA low-level routines
 *
 *  Maपूर्णांकained by:  Tejun Heo <tj@kernel.org>
 *    		    Please ALWAYS copy linux-ide@vger.kernel.org
 *		    on emails.
 *
 *  Copyright 2004-2005 Red Hat, Inc.
 *
 * libata करोcumentation is available via 'make {ps|pdf}docs',
 * as Documentation/driver-api/libata.rst
 *
 * AHCI hardware करोcumentation:
 * http://www.पूर्णांकel.com/technology/serialata/pdf/rev1_0.pdf
 * http://www.पूर्णांकel.com/technology/serialata/pdf/rev1_1.pdf
 */

#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/nospec.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <linux/libata.h>
#समावेश <linux/pci.h>
#समावेश "ahci.h"
#समावेश "libata.h"

अटल पूर्णांक ahci_skip_host_reset;
पूर्णांक ahci_ignore_sss;
EXPORT_SYMBOL_GPL(ahci_ignore_sss);

module_param_named(skip_host_reset, ahci_skip_host_reset, पूर्णांक, 0444);
MODULE_PARM_DESC(skip_host_reset, "skip global host reset (0=don't skip, 1=skip)");

module_param_named(ignore_sss, ahci_ignore_sss, पूर्णांक, 0444);
MODULE_PARM_DESC(ignore_sss, "Ignore staggered spinup flag (0=don't ignore, 1=ignore)");

अटल पूर्णांक ahci_set_lpm(काष्ठा ata_link *link, क्रमागत ata_lpm_policy policy,
			अचिन्हित hपूर्णांकs);
अटल sमाप_प्रकार ahci_led_show(काष्ठा ata_port *ap, अक्षर *buf);
अटल sमाप_प्रकार ahci_led_store(काष्ठा ata_port *ap, स्थिर अक्षर *buf,
			      माप_प्रकार size);
अटल sमाप_प्रकार ahci_transmit_led_message(काष्ठा ata_port *ap, u32 state,
					sमाप_प्रकार size);



अटल पूर्णांक ahci_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val);
अटल पूर्णांक ahci_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val);
अटल bool ahci_qc_fill_rtf(काष्ठा ata_queued_cmd *qc);
अटल पूर्णांक ahci_port_start(काष्ठा ata_port *ap);
अटल व्योम ahci_port_stop(काष्ठा ata_port *ap);
अटल क्रमागत ata_completion_errors ahci_qc_prep(काष्ठा ata_queued_cmd *qc);
अटल पूर्णांक ahci_pmp_qc_defer(काष्ठा ata_queued_cmd *qc);
अटल व्योम ahci_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम ahci_thaw(काष्ठा ata_port *ap);
अटल व्योम ahci_set_aggressive_devslp(काष्ठा ata_port *ap, bool sleep);
अटल व्योम ahci_enable_fbs(काष्ठा ata_port *ap);
अटल व्योम ahci_disable_fbs(काष्ठा ata_port *ap);
अटल व्योम ahci_pmp_attach(काष्ठा ata_port *ap);
अटल व्योम ahci_pmp_detach(काष्ठा ata_port *ap);
अटल पूर्णांक ahci_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			  अचिन्हित दीर्घ deadline);
अटल पूर्णांक ahci_pmp_retry_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			  अचिन्हित दीर्घ deadline);
अटल पूर्णांक ahci_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			  अचिन्हित दीर्घ deadline);
अटल व्योम ahci_postreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class);
अटल व्योम ahci_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc);
अटल व्योम ahci_dev_config(काष्ठा ata_device *dev);
#अगर_घोषित CONFIG_PM
अटल पूर्णांक ahci_port_suspend(काष्ठा ata_port *ap, pm_message_t mesg);
#पूर्ण_अगर
अटल sमाप_प्रकार ahci_activity_show(काष्ठा ata_device *dev, अक्षर *buf);
अटल sमाप_प्रकार ahci_activity_store(काष्ठा ata_device *dev,
				   क्रमागत sw_activity val);
अटल व्योम ahci_init_sw_activity(काष्ठा ata_link *link);

अटल sमाप_प्रकार ahci_show_host_caps(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf);
अटल sमाप_प्रकार ahci_show_host_cap2(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf);
अटल sमाप_प्रकार ahci_show_host_version(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf);
अटल sमाप_प्रकार ahci_show_port_cmd(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf);
अटल sमाप_प्रकार ahci_पढ़ो_em_buffer(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf);
अटल sमाप_प्रकार ahci_store_em_buffer(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार size);
अटल sमाप_प्रकार ahci_show_em_supported(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf);
अटल irqवापस_t ahci_single_level_irq_पूर्णांकr(पूर्णांक irq, व्योम *dev_instance);

अटल DEVICE_ATTR(ahci_host_caps, S_IRUGO, ahci_show_host_caps, शून्य);
अटल DEVICE_ATTR(ahci_host_cap2, S_IRUGO, ahci_show_host_cap2, शून्य);
अटल DEVICE_ATTR(ahci_host_version, S_IRUGO, ahci_show_host_version, शून्य);
अटल DEVICE_ATTR(ahci_port_cmd, S_IRUGO, ahci_show_port_cmd, शून्य);
अटल DEVICE_ATTR(em_buffer, S_IWUSR | S_IRUGO,
		   ahci_पढ़ो_em_buffer, ahci_store_em_buffer);
अटल DEVICE_ATTR(em_message_supported, S_IRUGO, ahci_show_em_supported, शून्य);

काष्ठा device_attribute *ahci_shost_attrs[] = अणु
	&dev_attr_link_घातer_management_policy,
	&dev_attr_em_message_type,
	&dev_attr_em_message,
	&dev_attr_ahci_host_caps,
	&dev_attr_ahci_host_cap2,
	&dev_attr_ahci_host_version,
	&dev_attr_ahci_port_cmd,
	&dev_attr_em_buffer,
	&dev_attr_em_message_supported,
	शून्य
पूर्ण;
EXPORT_SYMBOL_GPL(ahci_shost_attrs);

काष्ठा device_attribute *ahci_sdev_attrs[] = अणु
	&dev_attr_sw_activity,
	&dev_attr_unload_heads,
	&dev_attr_ncq_prio_enable,
	शून्य
पूर्ण;
EXPORT_SYMBOL_GPL(ahci_sdev_attrs);

काष्ठा ata_port_operations ahci_ops = अणु
	.inherits		= &sata_pmp_port_ops,

	.qc_defer		= ahci_pmp_qc_defer,
	.qc_prep		= ahci_qc_prep,
	.qc_issue		= ahci_qc_issue,
	.qc_fill_rtf		= ahci_qc_fill_rtf,

	.मुक्तze			= ahci_मुक्तze,
	.thaw			= ahci_thaw,
	.softreset		= ahci_softreset,
	.hardreset		= ahci_hardreset,
	.postreset		= ahci_postreset,
	.pmp_softreset		= ahci_softreset,
	.error_handler		= ahci_error_handler,
	.post_पूर्णांकernal_cmd	= ahci_post_पूर्णांकernal_cmd,
	.dev_config		= ahci_dev_config,

	.scr_पढ़ो		= ahci_scr_पढ़ो,
	.scr_ग_लिखो		= ahci_scr_ग_लिखो,
	.pmp_attach		= ahci_pmp_attach,
	.pmp_detach		= ahci_pmp_detach,

	.set_lpm		= ahci_set_lpm,
	.em_show		= ahci_led_show,
	.em_store		= ahci_led_store,
	.sw_activity_show	= ahci_activity_show,
	.sw_activity_store	= ahci_activity_store,
	.transmit_led_message	= ahci_transmit_led_message,
#अगर_घोषित CONFIG_PM
	.port_suspend		= ahci_port_suspend,
	.port_resume		= ahci_port_resume,
#पूर्ण_अगर
	.port_start		= ahci_port_start,
	.port_stop		= ahci_port_stop,
पूर्ण;
EXPORT_SYMBOL_GPL(ahci_ops);

काष्ठा ata_port_operations ahci_pmp_retry_srst_ops = अणु
	.inherits		= &ahci_ops,
	.softreset		= ahci_pmp_retry_softreset,
पूर्ण;
EXPORT_SYMBOL_GPL(ahci_pmp_retry_srst_ops);

अटल bool ahci_em_messages __पढ़ो_mostly = true;
module_param(ahci_em_messages, bool, 0444);
/* add other LED protocol types when they become supported */
MODULE_PARM_DESC(ahci_em_messages,
	"AHCI Enclosure Management Message control (0 = off, 1 = on)");

/* device sleep idle समयout in ms */
अटल पूर्णांक devslp_idle_समयout __पढ़ो_mostly = 1000;
module_param(devslp_idle_समयout, पूर्णांक, 0644);
MODULE_PARM_DESC(devslp_idle_समयout, "device sleep idle timeout");

अटल व्योम ahci_enable_ahci(व्योम __iomem *mmio)
अणु
	पूर्णांक i;
	u32 पंचांगp;

	/* turn on AHCI_EN */
	पंचांगp = पढ़ोl(mmio + HOST_CTL);
	अगर (पंचांगp & HOST_AHCI_EN)
		वापस;

	/* Some controllers need AHCI_EN to be written multiple बार.
	 * Try a few बार beक्रमe giving up.
	 */
	क्रम (i = 0; i < 5; i++) अणु
		पंचांगp |= HOST_AHCI_EN;
		ग_लिखोl(पंचांगp, mmio + HOST_CTL);
		पंचांगp = पढ़ोl(mmio + HOST_CTL);	/* flush && sanity check */
		अगर (पंचांगp & HOST_AHCI_EN)
			वापस;
		msleep(10);
	पूर्ण

	WARN_ON(1);
पूर्ण

/**
 *	ahci_rpm_get_port - Make sure the port is घातered on
 *	@ap: Port to घातer on
 *
 *	Whenever there is need to access the AHCI host रेजिस्टरs outside of
 *	normal execution paths, call this function to make sure the host is
 *	actually घातered on.
 */
अटल पूर्णांक ahci_rpm_get_port(काष्ठा ata_port *ap)
अणु
	वापस pm_runसमय_get_sync(ap->dev);
पूर्ण

/**
 *	ahci_rpm_put_port - Unकरोes ahci_rpm_get_port()
 *	@ap: Port to घातer करोwn
 *
 *	Unकरोes ahci_rpm_get_port() and possibly घातers करोwn the AHCI host
 *	अगर it has no more active users.
 */
अटल व्योम ahci_rpm_put_port(काष्ठा ata_port *ap)
अणु
	pm_runसमय_put(ap->dev);
पूर्ण

अटल sमाप_प्रकार ahci_show_host_caps(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(shost);
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;

	वापस प्र_लिखो(buf, "%x\n", hpriv->cap);
पूर्ण

अटल sमाप_प्रकार ahci_show_host_cap2(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(shost);
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;

	वापस प्र_लिखो(buf, "%x\n", hpriv->cap2);
पूर्ण

अटल sमाप_प्रकार ahci_show_host_version(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(shost);
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;

	वापस प्र_लिखो(buf, "%x\n", hpriv->version);
पूर्ण

अटल sमाप_प्रकार ahci_show_port_cmd(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(shost);
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	sमाप_प्रकार ret;

	ahci_rpm_get_port(ap);
	ret = प्र_लिखो(buf, "%x\n", पढ़ोl(port_mmio + PORT_CMD));
	ahci_rpm_put_port(ap);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ahci_पढ़ो_em_buffer(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(shost);
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	व्योम __iomem *em_mmio = mmio + hpriv->em_loc;
	u32 em_ctl, msg;
	अचिन्हित दीर्घ flags;
	माप_प्रकार count;
	पूर्णांक i;

	ahci_rpm_get_port(ap);
	spin_lock_irqsave(ap->lock, flags);

	em_ctl = पढ़ोl(mmio + HOST_EM_CTL);
	अगर (!(ap->flags & ATA_FLAG_EM) || em_ctl & EM_CTL_XMT ||
	    !(hpriv->em_msg_type & EM_MSG_TYPE_SGPIO)) अणु
		spin_unlock_irqrestore(ap->lock, flags);
		ahci_rpm_put_port(ap);
		वापस -EINVAL;
	पूर्ण

	अगर (!(em_ctl & EM_CTL_MR)) अणु
		spin_unlock_irqrestore(ap->lock, flags);
		ahci_rpm_put_port(ap);
		वापस -EAGAIN;
	पूर्ण

	अगर (!(em_ctl & EM_CTL_SMB))
		em_mmio += hpriv->em_buf_sz;

	count = hpriv->em_buf_sz;

	/* the count should not be larger than PAGE_SIZE */
	अगर (count > PAGE_SIZE) अणु
		अगर (prपूर्णांकk_ratelimit())
			ata_port_warn(ap,
				      "EM read buffer size too large: "
				      "buffer size %u, page size %lu\n",
				      hpriv->em_buf_sz, PAGE_SIZE);
		count = PAGE_SIZE;
	पूर्ण

	क्रम (i = 0; i < count; i += 4) अणु
		msg = पढ़ोl(em_mmio + i);
		buf[i] = msg & 0xff;
		buf[i + 1] = (msg >> 8) & 0xff;
		buf[i + 2] = (msg >> 16) & 0xff;
		buf[i + 3] = (msg >> 24) & 0xff;
	पूर्ण

	spin_unlock_irqrestore(ap->lock, flags);
	ahci_rpm_put_port(ap);

	वापस i;
पूर्ण

अटल sमाप_प्रकार ahci_store_em_buffer(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(shost);
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	व्योम __iomem *em_mmio = mmio + hpriv->em_loc;
	स्थिर अचिन्हित अक्षर *msg_buf = buf;
	u32 em_ctl, msg;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* check size validity */
	अगर (!(ap->flags & ATA_FLAG_EM) ||
	    !(hpriv->em_msg_type & EM_MSG_TYPE_SGPIO) ||
	    size % 4 || size > hpriv->em_buf_sz)
		वापस -EINVAL;

	ahci_rpm_get_port(ap);
	spin_lock_irqsave(ap->lock, flags);

	em_ctl = पढ़ोl(mmio + HOST_EM_CTL);
	अगर (em_ctl & EM_CTL_TM) अणु
		spin_unlock_irqrestore(ap->lock, flags);
		ahci_rpm_put_port(ap);
		वापस -EBUSY;
	पूर्ण

	क्रम (i = 0; i < size; i += 4) अणु
		msg = msg_buf[i] | msg_buf[i + 1] << 8 |
		      msg_buf[i + 2] << 16 | msg_buf[i + 3] << 24;
		ग_लिखोl(msg, em_mmio + i);
	पूर्ण

	ग_लिखोl(em_ctl | EM_CTL_TM, mmio + HOST_EM_CTL);

	spin_unlock_irqrestore(ap->lock, flags);
	ahci_rpm_put_port(ap);

	वापस size;
पूर्ण

अटल sमाप_प्रकार ahci_show_em_supported(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(shost);
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	u32 em_ctl;

	ahci_rpm_get_port(ap);
	em_ctl = पढ़ोl(mmio + HOST_EM_CTL);
	ahci_rpm_put_port(ap);

	वापस प्र_लिखो(buf, "%s%s%s%s\n",
		       em_ctl & EM_CTL_LED ? "led " : "",
		       em_ctl & EM_CTL_SAFTE ? "saf-te " : "",
		       em_ctl & EM_CTL_SES ? "ses-2 " : "",
		       em_ctl & EM_CTL_SGPIO ? "sgpio " : "");
पूर्ण

/**
 *	ahci_save_initial_config - Save and fixup initial config values
 *	@dev: target AHCI device
 *	@hpriv: host निजी area to store config values
 *
 *	Some रेजिस्टरs containing configuration info might be setup by
 *	BIOS and might be cleared on reset.  This function saves the
 *	initial values of those रेजिस्टरs पूर्णांकo @hpriv such that they
 *	can be restored after controller reset.
 *
 *	If inconsistent, config values are fixed up by this function.
 *
 *	If it is not set alपढ़ोy this function sets hpriv->start_engine to
 *	ahci_start_engine.
 *
 *	LOCKING:
 *	None.
 */
व्योम ahci_save_initial_config(काष्ठा device *dev, काष्ठा ahci_host_priv *hpriv)
अणु
	व्योम __iomem *mmio = hpriv->mmio;
	u32 cap, cap2, vers, port_map;
	पूर्णांक i;

	/* make sure AHCI mode is enabled beक्रमe accessing CAP */
	ahci_enable_ahci(mmio);

	/* Values prefixed with saved_ are written back to host after
	 * reset.  Values without are used क्रम driver operation.
	 */
	hpriv->saved_cap = cap = पढ़ोl(mmio + HOST_CAP);
	hpriv->saved_port_map = port_map = पढ़ोl(mmio + HOST_PORTS_IMPL);

	/* CAP2 रेजिस्टर is only defined क्रम AHCI 1.2 and later */
	vers = पढ़ोl(mmio + HOST_VERSION);
	अगर ((vers >> 16) > 1 ||
	   ((vers >> 16) == 1 && (vers & 0xFFFF) >= 0x200))
		hpriv->saved_cap2 = cap2 = पढ़ोl(mmio + HOST_CAP2);
	अन्यथा
		hpriv->saved_cap2 = cap2 = 0;

	/* some chips have errata preventing 64bit use */
	अगर ((cap & HOST_CAP_64) && (hpriv->flags & AHCI_HFLAG_32BIT_ONLY)) अणु
		dev_info(dev, "controller can't do 64bit DMA, forcing 32bit\n");
		cap &= ~HOST_CAP_64;
	पूर्ण

	अगर ((cap & HOST_CAP_NCQ) && (hpriv->flags & AHCI_HFLAG_NO_NCQ)) अणु
		dev_info(dev, "controller can't do NCQ, turning off CAP_NCQ\n");
		cap &= ~HOST_CAP_NCQ;
	पूर्ण

	अगर (!(cap & HOST_CAP_NCQ) && (hpriv->flags & AHCI_HFLAG_YES_NCQ)) अणु
		dev_info(dev, "controller can do NCQ, turning on CAP_NCQ\n");
		cap |= HOST_CAP_NCQ;
	पूर्ण

	अगर ((cap & HOST_CAP_PMP) && (hpriv->flags & AHCI_HFLAG_NO_PMP)) अणु
		dev_info(dev, "controller can't do PMP, turning off CAP_PMP\n");
		cap &= ~HOST_CAP_PMP;
	पूर्ण

	अगर ((cap & HOST_CAP_SNTF) && (hpriv->flags & AHCI_HFLAG_NO_SNTF)) अणु
		dev_info(dev,
			 "controller can't do SNTF, turning off CAP_SNTF\n");
		cap &= ~HOST_CAP_SNTF;
	पूर्ण

	अगर ((cap2 & HOST_CAP2_SDS) && (hpriv->flags & AHCI_HFLAG_NO_DEVSLP)) अणु
		dev_info(dev,
			 "controller can't do DEVSLP, turning off\n");
		cap2 &= ~HOST_CAP2_SDS;
		cap2 &= ~HOST_CAP2_SADM;
	पूर्ण

	अगर (!(cap & HOST_CAP_FBS) && (hpriv->flags & AHCI_HFLAG_YES_FBS)) अणु
		dev_info(dev, "controller can do FBS, turning on CAP_FBS\n");
		cap |= HOST_CAP_FBS;
	पूर्ण

	अगर ((cap & HOST_CAP_FBS) && (hpriv->flags & AHCI_HFLAG_NO_FBS)) अणु
		dev_info(dev, "controller can't do FBS, turning off CAP_FBS\n");
		cap &= ~HOST_CAP_FBS;
	पूर्ण

	अगर (!(cap & HOST_CAP_ALPM) && (hpriv->flags & AHCI_HFLAG_YES_ALPM)) अणु
		dev_info(dev, "controller can do ALPM, turning on CAP_ALPM\n");
		cap |= HOST_CAP_ALPM;
	पूर्ण

	अगर ((cap & HOST_CAP_SXS) && (hpriv->flags & AHCI_HFLAG_NO_SXS)) अणु
		dev_info(dev, "controller does not support SXS, disabling CAP_SXS\n");
		cap &= ~HOST_CAP_SXS;
	पूर्ण

	अगर (hpriv->क्रमce_port_map && port_map != hpriv->क्रमce_port_map) अणु
		dev_info(dev, "forcing port_map 0x%x -> 0x%x\n",
			 port_map, hpriv->क्रमce_port_map);
		port_map = hpriv->क्रमce_port_map;
		hpriv->saved_port_map = port_map;
	पूर्ण

	अगर (hpriv->mask_port_map) अणु
		dev_warn(dev, "masking port_map 0x%x -> 0x%x\n",
			port_map,
			port_map & hpriv->mask_port_map);
		port_map &= hpriv->mask_port_map;
	पूर्ण

	/* cross check port_map and cap.n_ports */
	अगर (port_map) अणु
		पूर्णांक map_ports = 0;

		क्रम (i = 0; i < AHCI_MAX_PORTS; i++)
			अगर (port_map & (1 << i))
				map_ports++;

		/* If PI has more ports than n_ports, whine, clear
		 * port_map and let it be generated from n_ports.
		 */
		अगर (map_ports > ahci_nr_ports(cap)) अणु
			dev_warn(dev,
				 "implemented port map (0x%x) contains more ports than nr_ports (%u), using nr_ports\n",
				 port_map, ahci_nr_ports(cap));
			port_map = 0;
		पूर्ण
	पूर्ण

	/* fabricate port_map from cap.nr_ports क्रम < AHCI 1.3 */
	अगर (!port_map && vers < 0x10300) अणु
		port_map = (1 << ahci_nr_ports(cap)) - 1;
		dev_warn(dev, "forcing PORTS_IMPL to 0x%x\n", port_map);

		/* ग_लिखो the fixed up value to the PI रेजिस्टर */
		hpriv->saved_port_map = port_map;
	पूर्ण

	/* record values to use during operation */
	hpriv->cap = cap;
	hpriv->cap2 = cap2;
	hpriv->version = पढ़ोl(mmio + HOST_VERSION);
	hpriv->port_map = port_map;

	अगर (!hpriv->start_engine)
		hpriv->start_engine = ahci_start_engine;

	अगर (!hpriv->stop_engine)
		hpriv->stop_engine = ahci_stop_engine;

	अगर (!hpriv->irq_handler)
		hpriv->irq_handler = ahci_single_level_irq_पूर्णांकr;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_save_initial_config);

/**
 *	ahci_restore_initial_config - Restore initial config
 *	@host: target ATA host
 *
 *	Restore initial config stored by ahci_save_initial_config().
 *
 *	LOCKING:
 *	None.
 */
अटल व्योम ahci_restore_initial_config(काष्ठा ata_host *host)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;

	ग_लिखोl(hpriv->saved_cap, mmio + HOST_CAP);
	अगर (hpriv->saved_cap2)
		ग_लिखोl(hpriv->saved_cap2, mmio + HOST_CAP2);
	ग_लिखोl(hpriv->saved_port_map, mmio + HOST_PORTS_IMPL);
	(व्योम) पढ़ोl(mmio + HOST_PORTS_IMPL);	/* flush */
पूर्ण

अटल अचिन्हित ahci_scr_offset(काष्ठा ata_port *ap, अचिन्हित पूर्णांक sc_reg)
अणु
	अटल स्थिर पूर्णांक offset[] = अणु
		[SCR_STATUS]		= PORT_SCR_STAT,
		[SCR_CONTROL]		= PORT_SCR_CTL,
		[SCR_ERROR]		= PORT_SCR_ERR,
		[SCR_ACTIVE]		= PORT_SCR_ACT,
		[SCR_NOTIFICATION]	= PORT_SCR_NTF,
	पूर्ण;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;

	अगर (sc_reg < ARRAY_SIZE(offset) &&
	    (sc_reg != SCR_NOTIFICATION || (hpriv->cap & HOST_CAP_SNTF)))
		वापस offset[sc_reg];
	वापस 0;
पूर्ण

अटल पूर्णांक ahci_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(link->ap);
	पूर्णांक offset = ahci_scr_offset(link->ap, sc_reg);

	अगर (offset) अणु
		*val = पढ़ोl(port_mmio + offset);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ahci_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(link->ap);
	पूर्णांक offset = ahci_scr_offset(link->ap, sc_reg);

	अगर (offset) अणु
		ग_लिखोl(val, port_mmio + offset);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

व्योम ahci_start_engine(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 पंचांगp;

	/* start DMA */
	पंचांगp = पढ़ोl(port_mmio + PORT_CMD);
	पंचांगp |= PORT_CMD_START;
	ग_लिखोl(पंचांगp, port_mmio + PORT_CMD);
	पढ़ोl(port_mmio + PORT_CMD); /* flush */
पूर्ण
EXPORT_SYMBOL_GPL(ahci_start_engine);

पूर्णांक ahci_stop_engine(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	u32 पंचांगp;

	/*
	 * On some controllers, stopping a port's DMA engine जबतक the port
	 * is in ALPM state (partial or slumber) results in failures on
	 * subsequent DMA engine starts.  For those controllers, put the
	 * port back in active state beक्रमe stopping its DMA engine.
	 */
	अगर ((hpriv->flags & AHCI_HFLAG_WAKE_BEFORE_STOP) &&
	    (ap->link.lpm_policy > ATA_LPM_MAX_POWER) &&
	    ahci_set_lpm(&ap->link, ATA_LPM_MAX_POWER, ATA_LPM_WAKE_ONLY)) अणु
		dev_err(ap->host->dev, "Failed to wake up port before engine stop\n");
		वापस -EIO;
	पूर्ण

	पंचांगp = पढ़ोl(port_mmio + PORT_CMD);

	/* check अगर the HBA is idle */
	अगर ((पंचांगp & (PORT_CMD_START | PORT_CMD_LIST_ON)) == 0)
		वापस 0;

	/*
	 * Don't try to issue commands but वापस with ENODEV अगर the
	 * AHCI controller not available anymore (e.g. due to PCIe hot
	 * unplugging). Otherwise a 500ms delay क्रम each port is added.
	 */
	अगर (पंचांगp == 0xffffffff) अणु
		dev_err(ap->host->dev, "AHCI controller unavailable!\n");
		वापस -ENODEV;
	पूर्ण

	/* setting HBA to idle */
	पंचांगp &= ~PORT_CMD_START;
	ग_लिखोl(पंचांगp, port_mmio + PORT_CMD);

	/* रुको क्रम engine to stop. This could be as दीर्घ as 500 msec */
	पंचांगp = ata_रुको_रेजिस्टर(ap, port_mmio + PORT_CMD,
				PORT_CMD_LIST_ON, PORT_CMD_LIST_ON, 1, 500);
	अगर (पंचांगp & PORT_CMD_LIST_ON)
		वापस -EIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_stop_engine);

व्योम ahci_start_fis_rx(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	u32 पंचांगp;

	/* set FIS रेजिस्टरs */
	अगर (hpriv->cap & HOST_CAP_64)
		ग_लिखोl((pp->cmd_slot_dma >> 16) >> 16,
		       port_mmio + PORT_LST_ADDR_HI);
	ग_लिखोl(pp->cmd_slot_dma & 0xffffffff, port_mmio + PORT_LST_ADDR);

	अगर (hpriv->cap & HOST_CAP_64)
		ग_लिखोl((pp->rx_fis_dma >> 16) >> 16,
		       port_mmio + PORT_FIS_ADDR_HI);
	ग_लिखोl(pp->rx_fis_dma & 0xffffffff, port_mmio + PORT_FIS_ADDR);

	/* enable FIS reception */
	पंचांगp = पढ़ोl(port_mmio + PORT_CMD);
	पंचांगp |= PORT_CMD_FIS_RX;
	ग_लिखोl(पंचांगp, port_mmio + PORT_CMD);

	/* flush */
	पढ़ोl(port_mmio + PORT_CMD);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_start_fis_rx);

अटल पूर्णांक ahci_stop_fis_rx(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 पंचांगp;

	/* disable FIS reception */
	पंचांगp = पढ़ोl(port_mmio + PORT_CMD);
	पंचांगp &= ~PORT_CMD_FIS_RX;
	ग_लिखोl(पंचांगp, port_mmio + PORT_CMD);

	/* रुको क्रम completion, spec says 500ms, give it 1000 */
	पंचांगp = ata_रुको_रेजिस्टर(ap, port_mmio + PORT_CMD, PORT_CMD_FIS_ON,
				PORT_CMD_FIS_ON, 10, 1000);
	अगर (पंचांगp & PORT_CMD_FIS_ON)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल व्योम ahci_घातer_up(काष्ठा ata_port *ap)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 cmd;

	cmd = पढ़ोl(port_mmio + PORT_CMD) & ~PORT_CMD_ICC_MASK;

	/* spin up device */
	अगर (hpriv->cap & HOST_CAP_SSS) अणु
		cmd |= PORT_CMD_SPIN_UP;
		ग_लिखोl(cmd, port_mmio + PORT_CMD);
	पूर्ण

	/* wake up link */
	ग_लिखोl(cmd | PORT_CMD_ICC_ACTIVE, port_mmio + PORT_CMD);
पूर्ण

अटल पूर्णांक ahci_set_lpm(काष्ठा ata_link *link, क्रमागत ata_lpm_policy policy,
			अचिन्हित पूर्णांक hपूर्णांकs)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	व्योम __iomem *port_mmio = ahci_port_base(ap);

	अगर (policy != ATA_LPM_MAX_POWER) अणु
		/* wakeup flag only applies to the max घातer policy */
		hपूर्णांकs &= ~ATA_LPM_WAKE_ONLY;

		/*
		 * Disable पूर्णांकerrupts on Phy Ready. This keeps us from
		 * getting woken up due to spurious phy पढ़ोy
		 * पूर्णांकerrupts.
		 */
		pp->पूर्णांकr_mask &= ~PORT_IRQ_PHYRDY;
		ग_लिखोl(pp->पूर्णांकr_mask, port_mmio + PORT_IRQ_MASK);

		sata_link_scr_lpm(link, policy, false);
	पूर्ण

	अगर (hpriv->cap & HOST_CAP_ALPM) अणु
		u32 cmd = पढ़ोl(port_mmio + PORT_CMD);

		अगर (policy == ATA_LPM_MAX_POWER || !(hपूर्णांकs & ATA_LPM_HIPM)) अणु
			अगर (!(hपूर्णांकs & ATA_LPM_WAKE_ONLY))
				cmd &= ~(PORT_CMD_ASP | PORT_CMD_ALPE);
			cmd |= PORT_CMD_ICC_ACTIVE;

			ग_लिखोl(cmd, port_mmio + PORT_CMD);
			पढ़ोl(port_mmio + PORT_CMD);

			/* रुको 10ms to be sure we've come out of LPM state */
			ata_msleep(ap, 10);

			अगर (hपूर्णांकs & ATA_LPM_WAKE_ONLY)
				वापस 0;
		पूर्ण अन्यथा अणु
			cmd |= PORT_CMD_ALPE;
			अगर (policy == ATA_LPM_MIN_POWER)
				cmd |= PORT_CMD_ASP;
			अन्यथा अगर (policy == ATA_LPM_MIN_POWER_WITH_PARTIAL)
				cmd &= ~PORT_CMD_ASP;

			/* ग_लिखो out new cmd value */
			ग_लिखोl(cmd, port_mmio + PORT_CMD);
		पूर्ण
	पूर्ण

	/* set aggressive device sleep */
	अगर ((hpriv->cap2 & HOST_CAP2_SDS) &&
	    (hpriv->cap2 & HOST_CAP2_SADM) &&
	    (link->device->flags & ATA_DFLAG_DEVSLP)) अणु
		अगर (policy == ATA_LPM_MIN_POWER ||
		    policy == ATA_LPM_MIN_POWER_WITH_PARTIAL)
			ahci_set_aggressive_devslp(ap, true);
		अन्यथा
			ahci_set_aggressive_devslp(ap, false);
	पूर्ण

	अगर (policy == ATA_LPM_MAX_POWER) अणु
		sata_link_scr_lpm(link, policy, false);

		/* turn PHYRDY IRQ back on */
		pp->पूर्णांकr_mask |= PORT_IRQ_PHYRDY;
		ग_लिखोl(pp->पूर्णांकr_mask, port_mmio + PORT_IRQ_MASK);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम ahci_घातer_करोwn(काष्ठा ata_port *ap)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 cmd, scontrol;

	अगर (!(hpriv->cap & HOST_CAP_SSS))
		वापस;

	/* put device पूर्णांकo listen mode, first set PxSCTL.DET to 0 */
	scontrol = पढ़ोl(port_mmio + PORT_SCR_CTL);
	scontrol &= ~0xf;
	ग_लिखोl(scontrol, port_mmio + PORT_SCR_CTL);

	/* then set PxCMD.SUD to 0 */
	cmd = पढ़ोl(port_mmio + PORT_CMD) & ~PORT_CMD_ICC_MASK;
	cmd &= ~PORT_CMD_SPIN_UP;
	ग_लिखोl(cmd, port_mmio + PORT_CMD);
पूर्ण
#पूर्ण_अगर

अटल व्योम ahci_start_port(काष्ठा ata_port *ap)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ata_link *link;
	काष्ठा ahci_em_priv *emp;
	sमाप_प्रकार rc;
	पूर्णांक i;

	/* enable FIS reception */
	ahci_start_fis_rx(ap);

	/* enable DMA */
	अगर (!(hpriv->flags & AHCI_HFLAG_DELAY_ENGINE))
		hpriv->start_engine(ap);

	/* turn on LEDs */
	अगर (ap->flags & ATA_FLAG_EM) अणु
		ata_क्रम_each_link(link, ap, EDGE) अणु
			emp = &pp->em_priv[link->pmp];

			/* EM Transmit bit maybe busy during init */
			क्रम (i = 0; i < EM_MAX_RETRY; i++) अणु
				rc = ap->ops->transmit_led_message(ap,
							       emp->led_state,
							       4);
				/*
				 * If busy, give a breather but करो not
				 * release EH ownership by using msleep()
				 * instead of ata_msleep().  EM Transmit
				 * bit is busy क्रम the whole host and
				 * releasing ownership will cause other
				 * ports to fail the same way.
				 */
				अगर (rc == -EBUSY)
					msleep(1);
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ap->flags & ATA_FLAG_SW_ACTIVITY)
		ata_क्रम_each_link(link, ap, EDGE)
			ahci_init_sw_activity(link);

पूर्ण

अटल पूर्णांक ahci_deinit_port(काष्ठा ata_port *ap, स्थिर अक्षर **emsg)
अणु
	पूर्णांक rc;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;

	/* disable DMA */
	rc = hpriv->stop_engine(ap);
	अगर (rc) अणु
		*emsg = "failed to stop engine";
		वापस rc;
	पूर्ण

	/* disable FIS reception */
	rc = ahci_stop_fis_rx(ap);
	अगर (rc) अणु
		*emsg = "failed stop FIS RX";
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ahci_reset_controller(काष्ठा ata_host *host)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	u32 पंचांगp;

	/* we must be in AHCI mode, beक्रमe using anything
	 * AHCI-specअगरic, such as HOST_RESET.
	 */
	ahci_enable_ahci(mmio);

	/* global controller reset */
	अगर (!ahci_skip_host_reset) अणु
		पंचांगp = पढ़ोl(mmio + HOST_CTL);
		अगर ((पंचांगp & HOST_RESET) == 0) अणु
			ग_लिखोl(पंचांगp | HOST_RESET, mmio + HOST_CTL);
			पढ़ोl(mmio + HOST_CTL); /* flush */
		पूर्ण

		/*
		 * to perक्रमm host reset, OS should set HOST_RESET
		 * and poll until this bit is पढ़ो to be "0".
		 * reset must complete within 1 second, or
		 * the hardware should be considered fried.
		 */
		पंचांगp = ata_रुको_रेजिस्टर(शून्य, mmio + HOST_CTL, HOST_RESET,
					HOST_RESET, 10, 1000);

		अगर (पंचांगp & HOST_RESET) अणु
			dev_err(host->dev, "controller reset failed (0x%x)\n",
				पंचांगp);
			वापस -EIO;
		पूर्ण

		/* turn on AHCI mode */
		ahci_enable_ahci(mmio);

		/* Some रेजिस्टरs might be cleared on reset.  Restore
		 * initial values.
		 */
		अगर (!(hpriv->flags & AHCI_HFLAG_NO_WRITE_TO_RO))
			ahci_restore_initial_config(host);
	पूर्ण अन्यथा
		dev_info(host->dev, "skipping global host reset\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_reset_controller);

अटल व्योम ahci_sw_activity(काष्ठा ata_link *link)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ahci_em_priv *emp = &pp->em_priv[link->pmp];

	अगर (!(link->flags & ATA_LFLAG_SW_ACTIVITY))
		वापस;

	emp->activity++;
	अगर (!समयr_pending(&emp->समयr))
		mod_समयr(&emp->समयr, jअगरfies + msecs_to_jअगरfies(10));
पूर्ण

अटल व्योम ahci_sw_activity_blink(काष्ठा समयr_list *t)
अणु
	काष्ठा ahci_em_priv *emp = from_समयr(emp, t, समयr);
	काष्ठा ata_link *link = emp->link;
	काष्ठा ata_port *ap = link->ap;

	अचिन्हित दीर्घ led_message = emp->led_state;
	u32 activity_led_state;
	अचिन्हित दीर्घ flags;

	led_message &= EM_MSG_LED_VALUE;
	led_message |= ap->port_no | (link->pmp << 8);

	/* check to see अगर we've had activity.  If so,
	 * toggle state of LED and reset समयr.  If not,
	 * turn LED to desired idle state.
	 */
	spin_lock_irqsave(ap->lock, flags);
	अगर (emp->saved_activity != emp->activity) अणु
		emp->saved_activity = emp->activity;
		/* get the current LED state */
		activity_led_state = led_message & EM_MSG_LED_VALUE_ON;

		अगर (activity_led_state)
			activity_led_state = 0;
		अन्यथा
			activity_led_state = 1;

		/* clear old state */
		led_message &= ~EM_MSG_LED_VALUE_ACTIVITY;

		/* toggle state */
		led_message |= (activity_led_state << 16);
		mod_समयr(&emp->समयr, jअगरfies + msecs_to_jअगरfies(100));
	पूर्ण अन्यथा अणु
		/* चयन to idle */
		led_message &= ~EM_MSG_LED_VALUE_ACTIVITY;
		अगर (emp->blink_policy == BLINK_OFF)
			led_message |= (1 << 16);
	पूर्ण
	spin_unlock_irqrestore(ap->lock, flags);
	ap->ops->transmit_led_message(ap, led_message, 4);
पूर्ण

अटल व्योम ahci_init_sw_activity(काष्ठा ata_link *link)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ahci_em_priv *emp = &pp->em_priv[link->pmp];

	/* init activity stats, setup समयr */
	emp->saved_activity = emp->activity = 0;
	emp->link = link;
	समयr_setup(&emp->समयr, ahci_sw_activity_blink, 0);

	/* check our blink policy and set flag क्रम link अगर it's enabled */
	अगर (emp->blink_policy)
		link->flags |= ATA_LFLAG_SW_ACTIVITY;
पूर्ण

पूर्णांक ahci_reset_em(काष्ठा ata_host *host)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	u32 em_ctl;

	em_ctl = पढ़ोl(mmio + HOST_EM_CTL);
	अगर ((em_ctl & EM_CTL_TM) || (em_ctl & EM_CTL_RST))
		वापस -EINVAL;

	ग_लिखोl(em_ctl | EM_CTL_RST, mmio + HOST_EM_CTL);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_reset_em);

अटल sमाप_प्रकार ahci_transmit_led_message(काष्ठा ata_port *ap, u32 state,
					sमाप_प्रकार size)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	u32 em_ctl;
	u32 message[] = अणु0, 0पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक pmp;
	काष्ठा ahci_em_priv *emp;

	/* get the slot number from the message */
	pmp = (state & EM_MSG_LED_PMP_SLOT) >> 8;
	अगर (pmp < EM_MAX_SLOTS)
		emp = &pp->em_priv[pmp];
	अन्यथा
		वापस -EINVAL;

	ahci_rpm_get_port(ap);
	spin_lock_irqsave(ap->lock, flags);

	/*
	 * अगर we are still busy transmitting a previous message,
	 * करो not allow
	 */
	em_ctl = पढ़ोl(mmio + HOST_EM_CTL);
	अगर (em_ctl & EM_CTL_TM) अणु
		spin_unlock_irqrestore(ap->lock, flags);
		ahci_rpm_put_port(ap);
		वापस -EBUSY;
	पूर्ण

	अगर (hpriv->em_msg_type & EM_MSG_TYPE_LED) अणु
		/*
		 * create message header - this is all zero except क्रम
		 * the message size, which is 4 bytes.
		 */
		message[0] |= (4 << 8);

		/* ignore 0:4 of byte zero, fill in port info yourself */
		message[1] = ((state & ~EM_MSG_LED_HBA_PORT) | ap->port_no);

		/* ग_लिखो message to EM_LOC */
		ग_लिखोl(message[0], mmio + hpriv->em_loc);
		ग_लिखोl(message[1], mmio + hpriv->em_loc+4);

		/*
		 * tell hardware to transmit the message
		 */
		ग_लिखोl(em_ctl | EM_CTL_TM, mmio + HOST_EM_CTL);
	पूर्ण

	/* save off new led state क्रम port/slot */
	emp->led_state = state;

	spin_unlock_irqrestore(ap->lock, flags);
	ahci_rpm_put_port(ap);

	वापस size;
पूर्ण

अटल sमाप_प्रकार ahci_led_show(काष्ठा ata_port *ap, अक्षर *buf)
अणु
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ata_link *link;
	काष्ठा ahci_em_priv *emp;
	पूर्णांक rc = 0;

	ata_क्रम_each_link(link, ap, EDGE) अणु
		emp = &pp->em_priv[link->pmp];
		rc += प्र_लिखो(buf, "%lx\n", emp->led_state);
	पूर्ण
	वापस rc;
पूर्ण

अटल sमाप_प्रकार ahci_led_store(काष्ठा ata_port *ap, स्थिर अक्षर *buf,
				माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक state;
	पूर्णांक pmp;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ahci_em_priv *emp;

	अगर (kstrtouपूर्णांक(buf, 0, &state) < 0)
		वापस -EINVAL;

	/* get the slot number from the message */
	pmp = (state & EM_MSG_LED_PMP_SLOT) >> 8;
	अगर (pmp < EM_MAX_SLOTS) अणु
		pmp = array_index_nospec(pmp, EM_MAX_SLOTS);
		emp = &pp->em_priv[pmp];
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/* mask off the activity bits अगर we are in sw_activity
	 * mode, user should turn off sw_activity beक्रमe setting
	 * activity led through em_message
	 */
	अगर (emp->blink_policy)
		state &= ~EM_MSG_LED_VALUE_ACTIVITY;

	वापस ap->ops->transmit_led_message(ap, state, size);
पूर्ण

अटल sमाप_प्रकार ahci_activity_store(काष्ठा ata_device *dev, क्रमागत sw_activity val)
अणु
	काष्ठा ata_link *link = dev->link;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ahci_em_priv *emp = &pp->em_priv[link->pmp];
	u32 port_led_state = emp->led_state;

	/* save the desired Activity LED behavior */
	अगर (val == OFF) अणु
		/* clear LFLAG */
		link->flags &= ~(ATA_LFLAG_SW_ACTIVITY);

		/* set the LED to OFF */
		port_led_state &= EM_MSG_LED_VALUE_OFF;
		port_led_state |= (ap->port_no | (link->pmp << 8));
		ap->ops->transmit_led_message(ap, port_led_state, 4);
	पूर्ण अन्यथा अणु
		link->flags |= ATA_LFLAG_SW_ACTIVITY;
		अगर (val == BLINK_OFF) अणु
			/* set LED to ON क्रम idle */
			port_led_state &= EM_MSG_LED_VALUE_OFF;
			port_led_state |= (ap->port_no | (link->pmp << 8));
			port_led_state |= EM_MSG_LED_VALUE_ON; /* check this */
			ap->ops->transmit_led_message(ap, port_led_state, 4);
		पूर्ण
	पूर्ण
	emp->blink_policy = val;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ahci_activity_show(काष्ठा ata_device *dev, अक्षर *buf)
अणु
	काष्ठा ata_link *link = dev->link;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ahci_em_priv *emp = &pp->em_priv[link->pmp];

	/* display the saved value of activity behavior क्रम this
	 * disk.
	 */
	वापस प्र_लिखो(buf, "%d\n", emp->blink_policy);
पूर्ण

अटल व्योम ahci_port_init(काष्ठा device *dev, काष्ठा ata_port *ap,
			   पूर्णांक port_no, व्योम __iomem *mmio,
			   व्योम __iomem *port_mmio)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	स्थिर अक्षर *emsg = शून्य;
	पूर्णांक rc;
	u32 पंचांगp;

	/* make sure port is not active */
	rc = ahci_deinit_port(ap, &emsg);
	अगर (rc)
		dev_warn(dev, "%s (%d)\n", emsg, rc);

	/* clear SError */
	पंचांगp = पढ़ोl(port_mmio + PORT_SCR_ERR);
	VPRINTK("PORT_SCR_ERR 0x%x\n", पंचांगp);
	ग_लिखोl(पंचांगp, port_mmio + PORT_SCR_ERR);

	/* clear port IRQ */
	पंचांगp = पढ़ोl(port_mmio + PORT_IRQ_STAT);
	VPRINTK("PORT_IRQ_STAT 0x%x\n", पंचांगp);
	अगर (पंचांगp)
		ग_लिखोl(पंचांगp, port_mmio + PORT_IRQ_STAT);

	ग_लिखोl(1 << port_no, mmio + HOST_IRQ_STAT);

	/* mark esata ports */
	पंचांगp = पढ़ोl(port_mmio + PORT_CMD);
	अगर ((पंचांगp & PORT_CMD_ESP) && (hpriv->cap & HOST_CAP_SXS))
		ap->pflags |= ATA_PFLAG_EXTERNAL;
पूर्ण

व्योम ahci_init_controller(काष्ठा ata_host *host)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	पूर्णांक i;
	व्योम __iomem *port_mmio;
	u32 पंचांगp;

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		port_mmio = ahci_port_base(ap);
		अगर (ata_port_is_dummy(ap))
			जारी;

		ahci_port_init(host->dev, ap, i, mmio, port_mmio);
	पूर्ण

	पंचांगp = पढ़ोl(mmio + HOST_CTL);
	VPRINTK("HOST_CTL 0x%x\n", पंचांगp);
	ग_लिखोl(पंचांगp | HOST_IRQ_EN, mmio + HOST_CTL);
	पंचांगp = पढ़ोl(mmio + HOST_CTL);
	VPRINTK("HOST_CTL 0x%x\n", पंचांगp);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_init_controller);

अटल व्योम ahci_dev_config(काष्ठा ata_device *dev)
अणु
	काष्ठा ahci_host_priv *hpriv = dev->link->ap->host->निजी_data;

	अगर (hpriv->flags & AHCI_HFLAG_SECT255) अणु
		dev->max_sectors = 255;
		ata_dev_info(dev,
			     "SB600 AHCI: limiting to 255 sectors per cmd\n");
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक ahci_dev_classअगरy(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	काष्ठा ata_taskfile tf;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(port_mmio + PORT_SIG);
	tf.lbah		= (पंचांगp >> 24)	& 0xff;
	tf.lbam		= (पंचांगp >> 16)	& 0xff;
	tf.lbal		= (पंचांगp >> 8)	& 0xff;
	tf.nsect	= (पंचांगp)		& 0xff;

	वापस ata_dev_classअगरy(&tf);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_dev_classअगरy);

व्योम ahci_fill_cmd_slot(काष्ठा ahci_port_priv *pp, अचिन्हित पूर्णांक tag,
			u32 opts)
अणु
	dma_addr_t cmd_tbl_dma;

	cmd_tbl_dma = pp->cmd_tbl_dma + tag * AHCI_CMD_TBL_SZ;

	pp->cmd_slot[tag].opts = cpu_to_le32(opts);
	pp->cmd_slot[tag].status = 0;
	pp->cmd_slot[tag].tbl_addr = cpu_to_le32(cmd_tbl_dma & 0xffffffff);
	pp->cmd_slot[tag].tbl_addr_hi = cpu_to_le32((cmd_tbl_dma >> 16) >> 16);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_fill_cmd_slot);

पूर्णांक ahci_kick_engine(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	u8 status = पढ़ोl(port_mmio + PORT_TFDATA) & 0xFF;
	u32 पंचांगp;
	पूर्णांक busy, rc;

	/* stop engine */
	rc = hpriv->stop_engine(ap);
	अगर (rc)
		जाओ out_restart;

	/* need to करो CLO?
	 * always करो CLO अगर PMP is attached (AHCI-1.3 9.2)
	 */
	busy = status & (ATA_BUSY | ATA_DRQ);
	अगर (!busy && !sata_pmp_attached(ap)) अणु
		rc = 0;
		जाओ out_restart;
	पूर्ण

	अगर (!(hpriv->cap & HOST_CAP_CLO)) अणु
		rc = -EOPNOTSUPP;
		जाओ out_restart;
	पूर्ण

	/* perक्रमm CLO */
	पंचांगp = पढ़ोl(port_mmio + PORT_CMD);
	पंचांगp |= PORT_CMD_CLO;
	ग_लिखोl(पंचांगp, port_mmio + PORT_CMD);

	rc = 0;
	पंचांगp = ata_रुको_रेजिस्टर(ap, port_mmio + PORT_CMD,
				PORT_CMD_CLO, PORT_CMD_CLO, 1, 500);
	अगर (पंचांगp & PORT_CMD_CLO)
		rc = -EIO;

	/* restart engine */
 out_restart:
	hpriv->start_engine(ap);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_kick_engine);

अटल पूर्णांक ahci_exec_polled_cmd(काष्ठा ata_port *ap, पूर्णांक pmp,
				काष्ठा ata_taskfile *tf, पूर्णांक is_cmd, u16 flags,
				अचिन्हित दीर्घ समयout_msec)
अणु
	स्थिर u32 cmd_fis_len = 5; /* five dwords */
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u8 *fis = pp->cmd_tbl;
	u32 पंचांगp;

	/* prep the command */
	ata_tf_to_fis(tf, pmp, is_cmd, fis);
	ahci_fill_cmd_slot(pp, 0, cmd_fis_len | flags | (pmp << 12));

	/* set port value क्रम softreset of Port Multiplier */
	अगर (pp->fbs_enabled && pp->fbs_last_dev != pmp) अणु
		पंचांगp = पढ़ोl(port_mmio + PORT_FBS);
		पंचांगp &= ~(PORT_FBS_DEV_MASK | PORT_FBS_DEC);
		पंचांगp |= pmp << PORT_FBS_DEV_OFFSET;
		ग_लिखोl(पंचांगp, port_mmio + PORT_FBS);
		pp->fbs_last_dev = pmp;
	पूर्ण

	/* issue & रुको */
	ग_लिखोl(1, port_mmio + PORT_CMD_ISSUE);

	अगर (समयout_msec) अणु
		पंचांगp = ata_रुको_रेजिस्टर(ap, port_mmio + PORT_CMD_ISSUE,
					0x1, 0x1, 1, समयout_msec);
		अगर (पंचांगp & 0x1) अणु
			ahci_kick_engine(ap);
			वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा
		पढ़ोl(port_mmio + PORT_CMD_ISSUE);	/* flush */

	वापस 0;
पूर्ण

पूर्णांक ahci_करो_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
		      पूर्णांक pmp, अचिन्हित दीर्घ deadline,
		      पूर्णांक (*check_पढ़ोy)(काष्ठा ata_link *link))
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	स्थिर अक्षर *reason = शून्य;
	अचिन्हित दीर्घ now, msecs;
	काष्ठा ata_taskfile tf;
	bool fbs_disabled = false;
	पूर्णांक rc;

	DPRINTK("ENTER\n");

	/* prepare क्रम SRST (AHCI-1.1 10.4.1) */
	rc = ahci_kick_engine(ap);
	अगर (rc && rc != -EOPNOTSUPP)
		ata_link_warn(link, "failed to reset engine (errno=%d)\n", rc);

	/*
	 * According to AHCI-1.2 9.3.9: अगर FBS is enable, software shall
	 * clear PxFBS.EN to '0' prior to issuing software reset to devices
	 * that is attached to port multiplier.
	 */
	अगर (!ata_is_host_link(link) && pp->fbs_enabled) अणु
		ahci_disable_fbs(ap);
		fbs_disabled = true;
	पूर्ण

	ata_tf_init(link->device, &tf);

	/* issue the first H2D Register FIS */
	msecs = 0;
	now = jअगरfies;
	अगर (समय_after(deadline, now))
		msecs = jअगरfies_to_msecs(deadline - now);

	tf.ctl |= ATA_SRST;
	अगर (ahci_exec_polled_cmd(ap, pmp, &tf, 0,
				 AHCI_CMD_RESET | AHCI_CMD_CLR_BUSY, msecs)) अणु
		rc = -EIO;
		reason = "1st FIS failed";
		जाओ fail;
	पूर्ण

	/* spec says at least 5us, but be generous and sleep क्रम 1ms */
	ata_msleep(ap, 1);

	/* issue the second H2D Register FIS */
	tf.ctl &= ~ATA_SRST;
	ahci_exec_polled_cmd(ap, pmp, &tf, 0, 0, 0);

	/* रुको क्रम link to become पढ़ोy */
	rc = ata_रुको_after_reset(link, deadline, check_पढ़ोy);
	अगर (rc == -EBUSY && hpriv->flags & AHCI_HFLAG_SRST_TOUT_IS_OFFLINE) अणु
		/*
		 * Workaround क्रम हालs where link online status can't
		 * be trusted.  Treat device पढ़ोiness समयout as link
		 * offline.
		 */
		ata_link_info(link, "device not ready, treating as offline\n");
		*class = ATA_DEV_NONE;
	पूर्ण अन्यथा अगर (rc) अणु
		/* link occupied, -ENODEV too is an error */
		reason = "device not ready";
		जाओ fail;
	पूर्ण अन्यथा
		*class = ahci_dev_classअगरy(ap);

	/* re-enable FBS अगर disabled beक्रमe */
	अगर (fbs_disabled)
		ahci_enable_fbs(ap);

	DPRINTK("EXIT, class=%u\n", *class);
	वापस 0;

 fail:
	ata_link_err(link, "softreset failed (%s)\n", reason);
	वापस rc;
पूर्ण

पूर्णांक ahci_check_पढ़ोy(काष्ठा ata_link *link)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(link->ap);
	u8 status = पढ़ोl(port_mmio + PORT_TFDATA) & 0xFF;

	वापस ata_check_पढ़ोy(status);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_check_पढ़ोy);

अटल पूर्णांक ahci_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			  अचिन्हित दीर्घ deadline)
अणु
	पूर्णांक pmp = sata_srst_pmp(link);

	DPRINTK("ENTER\n");

	वापस ahci_करो_softreset(link, class, pmp, deadline, ahci_check_पढ़ोy);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_करो_softreset);

अटल पूर्णांक ahci_bad_pmp_check_पढ़ोy(काष्ठा ata_link *link)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(link->ap);
	u8 status = पढ़ोl(port_mmio + PORT_TFDATA) & 0xFF;
	u32 irq_status = पढ़ोl(port_mmio + PORT_IRQ_STAT);

	/*
	 * There is no need to check TFDATA अगर BAD PMP is found due to HW bug,
	 * which can save समयout delay.
	 */
	अगर (irq_status & PORT_IRQ_BAD_PMP)
		वापस -EIO;

	वापस ata_check_पढ़ोy(status);
पूर्ण

अटल पूर्णांक ahci_pmp_retry_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
				    अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	पूर्णांक pmp = sata_srst_pmp(link);
	पूर्णांक rc;
	u32 irq_sts;

	DPRINTK("ENTER\n");

	rc = ahci_करो_softreset(link, class, pmp, deadline,
			       ahci_bad_pmp_check_पढ़ोy);

	/*
	 * Soft reset fails with IPMS set when PMP is enabled but
	 * SATA HDD/ODD is connected to SATA port, करो soft reset
	 * again to port 0.
	 */
	अगर (rc == -EIO) अणु
		irq_sts = पढ़ोl(port_mmio + PORT_IRQ_STAT);
		अगर (irq_sts & PORT_IRQ_BAD_PMP) अणु
			ata_link_warn(link,
					"applying PMP SRST workaround "
					"and retrying\n");
			rc = ahci_करो_softreset(link, class, 0, deadline,
					       ahci_check_पढ़ोy);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक ahci_करो_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
		      अचिन्हित दीर्घ deadline, bool *online)
अणु
	स्थिर अचिन्हित दीर्घ *timing = sata_ehc_deb_timing(&link->eh_context);
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	u8 *d2h_fis = pp->rx_fis + RX_FIS_D2H_REG;
	काष्ठा ata_taskfile tf;
	पूर्णांक rc;

	DPRINTK("ENTER\n");

	hpriv->stop_engine(ap);

	/* clear D2H reception area to properly रुको क्रम D2H FIS */
	ata_tf_init(link->device, &tf);
	tf.command = ATA_BUSY;
	ata_tf_to_fis(&tf, 0, 0, d2h_fis);

	rc = sata_link_hardreset(link, timing, deadline, online,
				 ahci_check_पढ़ोy);

	hpriv->start_engine(ap);

	अगर (*online)
		*class = ahci_dev_classअगरy(ap);

	DPRINTK("EXIT, rc=%d, class=%u\n", rc, *class);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_करो_hardreset);

अटल पूर्णांक ahci_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			  अचिन्हित दीर्घ deadline)
अणु
	bool online;

	वापस ahci_करो_hardreset(link, class, deadline, &online);
पूर्ण

अटल व्योम ahci_postreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class)
अणु
	काष्ठा ata_port *ap = link->ap;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 new_पंचांगp, पंचांगp;

	ata_std_postreset(link, class);

	/* Make sure port's ATAPI bit is set appropriately */
	new_पंचांगp = पंचांगp = पढ़ोl(port_mmio + PORT_CMD);
	अगर (*class == ATA_DEV_ATAPI)
		new_पंचांगp |= PORT_CMD_ATAPI;
	अन्यथा
		new_पंचांगp &= ~PORT_CMD_ATAPI;
	अगर (new_पंचांगp != पंचांगp) अणु
		ग_लिखोl(new_पंचांगp, port_mmio + PORT_CMD);
		पढ़ोl(port_mmio + PORT_CMD); /* flush */
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ahci_fill_sg(काष्ठा ata_queued_cmd *qc, व्योम *cmd_tbl)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा ahci_sg *ahci_sg = cmd_tbl + AHCI_CMD_TBL_HDR_SZ;
	अचिन्हित पूर्णांक si;

	VPRINTK("ENTER\n");

	/*
	 * Next, the S/G list.
	 */
	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		dma_addr_t addr = sg_dma_address(sg);
		u32 sg_len = sg_dma_len(sg);

		ahci_sg[si].addr = cpu_to_le32(addr & 0xffffffff);
		ahci_sg[si].addr_hi = cpu_to_le32((addr >> 16) >> 16);
		ahci_sg[si].flags_size = cpu_to_le32(sg_len - 1);
	पूर्ण

	वापस si;
पूर्ण

अटल पूर्णांक ahci_pmp_qc_defer(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;

	अगर (!sata_pmp_attached(ap) || pp->fbs_enabled)
		वापस ata_std_qc_defer(qc);
	अन्यथा
		वापस sata_pmp_qc_defer_cmd_चयन(qc);
पूर्ण

अटल क्रमागत ata_completion_errors ahci_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	पूर्णांक is_atapi = ata_is_atapi(qc->tf.protocol);
	व्योम *cmd_tbl;
	u32 opts;
	स्थिर u32 cmd_fis_len = 5; /* five dwords */
	अचिन्हित पूर्णांक n_elem;

	/*
	 * Fill in command table inक्रमmation.  First, the header,
	 * a SATA Register - Host to Device command FIS.
	 */
	cmd_tbl = pp->cmd_tbl + qc->hw_tag * AHCI_CMD_TBL_SZ;

	ata_tf_to_fis(&qc->tf, qc->dev->link->pmp, 1, cmd_tbl);
	अगर (is_atapi) अणु
		स_रखो(cmd_tbl + AHCI_CMD_TBL_CDB, 0, 32);
		स_नकल(cmd_tbl + AHCI_CMD_TBL_CDB, qc->cdb, qc->dev->cdb_len);
	पूर्ण

	n_elem = 0;
	अगर (qc->flags & ATA_QCFLAG_DMAMAP)
		n_elem = ahci_fill_sg(qc, cmd_tbl);

	/*
	 * Fill in command slot inक्रमmation.
	 */
	opts = cmd_fis_len | n_elem << 16 | (qc->dev->link->pmp << 12);
	अगर (qc->tf.flags & ATA_TFLAG_WRITE)
		opts |= AHCI_CMD_WRITE;
	अगर (is_atapi)
		opts |= AHCI_CMD_ATAPI | AHCI_CMD_PREFETCH;

	ahci_fill_cmd_slot(pp, qc->hw_tag, opts);

	वापस AC_ERR_OK;
पूर्ण

अटल व्योम ahci_fbs_dec_पूर्णांकr(काष्ठा ata_port *ap)
अणु
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 fbs = पढ़ोl(port_mmio + PORT_FBS);
	पूर्णांक retries = 3;

	DPRINTK("ENTER\n");
	BUG_ON(!pp->fbs_enabled);

	/* समय to रुको क्रम DEC is not specअगरied by AHCI spec,
	 * add a retry loop क्रम safety.
	 */
	ग_लिखोl(fbs | PORT_FBS_DEC, port_mmio + PORT_FBS);
	fbs = पढ़ोl(port_mmio + PORT_FBS);
	जबतक ((fbs & PORT_FBS_DEC) && retries--) अणु
		udelay(1);
		fbs = पढ़ोl(port_mmio + PORT_FBS);
	पूर्ण

	अगर (fbs & PORT_FBS_DEC)
		dev_err(ap->host->dev, "failed to clear device error\n");
पूर्ण

अटल व्योम ahci_error_पूर्णांकr(काष्ठा ata_port *ap, u32 irq_stat)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ata_eh_info *host_ehi = &ap->link.eh_info;
	काष्ठा ata_link *link = शून्य;
	काष्ठा ata_queued_cmd *active_qc;
	काष्ठा ata_eh_info *active_ehi;
	bool fbs_need_dec = false;
	u32 serror;

	/* determine active link with error */
	अगर (pp->fbs_enabled) अणु
		व्योम __iomem *port_mmio = ahci_port_base(ap);
		u32 fbs = पढ़ोl(port_mmio + PORT_FBS);
		पूर्णांक pmp = fbs >> PORT_FBS_DWE_OFFSET;

		अगर ((fbs & PORT_FBS_SDE) && (pmp < ap->nr_pmp_links)) अणु
			link = &ap->pmp_link[pmp];
			fbs_need_dec = true;
		पूर्ण

	पूर्ण अन्यथा
		ata_क्रम_each_link(link, ap, EDGE)
			अगर (ata_link_active(link))
				अवरोध;

	अगर (!link)
		link = &ap->link;

	active_qc = ata_qc_from_tag(ap, link->active_tag);
	active_ehi = &link->eh_info;

	/* record irq stat */
	ata_ehi_clear_desc(host_ehi);
	ata_ehi_push_desc(host_ehi, "irq_stat 0x%08x", irq_stat);

	/* AHCI needs SError cleared; otherwise, it might lock up */
	ahci_scr_पढ़ो(&ap->link, SCR_ERROR, &serror);
	ahci_scr_ग_लिखो(&ap->link, SCR_ERROR, serror);
	host_ehi->serror |= serror;

	/* some controllers set IRQ_IF_ERR on device errors, ignore it */
	अगर (hpriv->flags & AHCI_HFLAG_IGN_IRQ_IF_ERR)
		irq_stat &= ~PORT_IRQ_IF_ERR;

	अगर (irq_stat & PORT_IRQ_TF_ERR) अणु
		/* If qc is active, अक्षरge it; otherwise, the active
		 * link.  There's no active qc on NCQ errors.  It will
		 * be determined by EH by पढ़ोing log page 10h.
		 */
		अगर (active_qc)
			active_qc->err_mask |= AC_ERR_DEV;
		अन्यथा
			active_ehi->err_mask |= AC_ERR_DEV;

		अगर (hpriv->flags & AHCI_HFLAG_IGN_SERR_INTERNAL)
			host_ehi->serror &= ~SERR_INTERNAL;
	पूर्ण

	अगर (irq_stat & PORT_IRQ_UNK_FIS) अणु
		u32 *unk = pp->rx_fis + RX_FIS_UNK;

		active_ehi->err_mask |= AC_ERR_HSM;
		active_ehi->action |= ATA_EH_RESET;
		ata_ehi_push_desc(active_ehi,
				  "unknown FIS %08x %08x %08x %08x" ,
				  unk[0], unk[1], unk[2], unk[3]);
	पूर्ण

	अगर (sata_pmp_attached(ap) && (irq_stat & PORT_IRQ_BAD_PMP)) अणु
		active_ehi->err_mask |= AC_ERR_HSM;
		active_ehi->action |= ATA_EH_RESET;
		ata_ehi_push_desc(active_ehi, "incorrect PMP");
	पूर्ण

	अगर (irq_stat & (PORT_IRQ_HBUS_ERR | PORT_IRQ_HBUS_DATA_ERR)) अणु
		host_ehi->err_mask |= AC_ERR_HOST_BUS;
		host_ehi->action |= ATA_EH_RESET;
		ata_ehi_push_desc(host_ehi, "host bus error");
	पूर्ण

	अगर (irq_stat & PORT_IRQ_IF_ERR) अणु
		अगर (fbs_need_dec)
			active_ehi->err_mask |= AC_ERR_DEV;
		अन्यथा अणु
			host_ehi->err_mask |= AC_ERR_ATA_BUS;
			host_ehi->action |= ATA_EH_RESET;
		पूर्ण

		ata_ehi_push_desc(host_ehi, "interface fatal error");
	पूर्ण

	अगर (irq_stat & (PORT_IRQ_CONNECT | PORT_IRQ_PHYRDY)) अणु
		ata_ehi_hotplugged(host_ehi);
		ata_ehi_push_desc(host_ehi, "%s",
			irq_stat & PORT_IRQ_CONNECT ?
			"connection status changed" : "PHY RDY changed");
	पूर्ण

	/* okay, let's hand over to EH */

	अगर (irq_stat & PORT_IRQ_FREEZE)
		ata_port_मुक्तze(ap);
	अन्यथा अगर (fbs_need_dec) अणु
		ata_link_पात(link);
		ahci_fbs_dec_पूर्णांकr(ap);
	पूर्ण अन्यथा
		ata_port_पात(ap);
पूर्ण

अटल व्योम ahci_handle_port_पूर्णांकerrupt(काष्ठा ata_port *ap,
				       व्योम __iomem *port_mmio, u32 status)
अणु
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	पूर्णांक resetting = !!(ap->pflags & ATA_PFLAG_RESETTING);
	u32 qc_active = 0;
	पूर्णांक rc;

	/* ignore BAD_PMP जबतक resetting */
	अगर (unlikely(resetting))
		status &= ~PORT_IRQ_BAD_PMP;

	अगर (sata_lpm_ignore_phy_events(&ap->link)) अणु
		status &= ~PORT_IRQ_PHYRDY;
		ahci_scr_ग_लिखो(&ap->link, SCR_ERROR, SERR_PHYRDY_CHG);
	पूर्ण

	अगर (unlikely(status & PORT_IRQ_ERROR)) अणु
		ahci_error_पूर्णांकr(ap, status);
		वापस;
	पूर्ण

	अगर (status & PORT_IRQ_SDB_FIS) अणु
		/* If SNotअगरication is available, leave notअगरication
		 * handling to sata_async_notअगरication().  If not,
		 * emulate it by snooping SDB FIS RX area.
		 *
		 * Snooping FIS RX area is probably cheaper than
		 * poking SNotअगरication but some स्थिरrollers which
		 * implement SNotअगरication, ICH9 क्रम example, करोn't
		 * store AN SDB FIS पूर्णांकo receive area.
		 */
		अगर (hpriv->cap & HOST_CAP_SNTF)
			sata_async_notअगरication(ap);
		अन्यथा अणु
			/* If the 'N' bit in word 0 of the FIS is set,
			 * we just received asynchronous notअगरication.
			 * Tell libata about it.
			 *
			 * Lack of SNotअगरication should not appear in
			 * ahci 1.2, so the workaround is unnecessary
			 * when FBS is enabled.
			 */
			अगर (pp->fbs_enabled)
				WARN_ON_ONCE(1);
			अन्यथा अणु
				स्थिर __le32 *f = pp->rx_fis + RX_FIS_SDB;
				u32 f0 = le32_to_cpu(f[0]);
				अगर (f0 & (1 << 15))
					sata_async_notअगरication(ap);
			पूर्ण
		पूर्ण
	पूर्ण

	/* pp->active_link is not reliable once FBS is enabled, both
	 * PORT_SCR_ACT and PORT_CMD_ISSUE should be checked because
	 * NCQ and non-NCQ commands may be in flight at the same समय.
	 */
	अगर (pp->fbs_enabled) अणु
		अगर (ap->qc_active) अणु
			qc_active = पढ़ोl(port_mmio + PORT_SCR_ACT);
			qc_active |= पढ़ोl(port_mmio + PORT_CMD_ISSUE);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* pp->active_link is valid अगरf any command is in flight */
		अगर (ap->qc_active && pp->active_link->sactive)
			qc_active = पढ़ोl(port_mmio + PORT_SCR_ACT);
		अन्यथा
			qc_active = पढ़ोl(port_mmio + PORT_CMD_ISSUE);
	पूर्ण


	rc = ata_qc_complete_multiple(ap, qc_active);

	/* जबतक resetting, invalid completions are expected */
	अगर (unlikely(rc < 0 && !resetting)) अणु
		ehi->err_mask |= AC_ERR_HSM;
		ehi->action |= ATA_EH_RESET;
		ata_port_मुक्तze(ap);
	पूर्ण
पूर्ण

अटल व्योम ahci_port_पूर्णांकr(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 status;

	status = पढ़ोl(port_mmio + PORT_IRQ_STAT);
	ग_लिखोl(status, port_mmio + PORT_IRQ_STAT);

	ahci_handle_port_पूर्णांकerrupt(ap, port_mmio, status);
पूर्ण

अटल irqवापस_t ahci_multi_irqs_पूर्णांकr_hard(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_port *ap = dev_instance;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 status;

	VPRINTK("ENTER\n");

	status = पढ़ोl(port_mmio + PORT_IRQ_STAT);
	ग_लिखोl(status, port_mmio + PORT_IRQ_STAT);

	spin_lock(ap->lock);
	ahci_handle_port_पूर्णांकerrupt(ap, port_mmio, status);
	spin_unlock(ap->lock);

	VPRINTK("EXIT\n");

	वापस IRQ_HANDLED;
पूर्ण

u32 ahci_handle_port_पूर्णांकr(काष्ठा ata_host *host, u32 irq_masked)
अणु
	अचिन्हित पूर्णांक i, handled = 0;

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap;

		अगर (!(irq_masked & (1 << i)))
			जारी;

		ap = host->ports[i];
		अगर (ap) अणु
			ahci_port_पूर्णांकr(ap);
			VPRINTK("port %u\n", i);
		पूर्ण अन्यथा अणु
			VPRINTK("port %u (no irq)\n", i);
			अगर (ata_ratelimit())
				dev_warn(host->dev,
					 "interrupt on disabled port %u\n", i);
		पूर्ण

		handled = 1;
	पूर्ण

	वापस handled;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_handle_port_पूर्णांकr);

अटल irqवापस_t ahci_single_level_irq_पूर्णांकr(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	काष्ठा ahci_host_priv *hpriv;
	अचिन्हित पूर्णांक rc = 0;
	व्योम __iomem *mmio;
	u32 irq_stat, irq_masked;

	VPRINTK("ENTER\n");

	hpriv = host->निजी_data;
	mmio = hpriv->mmio;

	/* sigh.  0xffffffff is a valid वापस from h/w */
	irq_stat = पढ़ोl(mmio + HOST_IRQ_STAT);
	अगर (!irq_stat)
		वापस IRQ_NONE;

	irq_masked = irq_stat & hpriv->port_map;

	spin_lock(&host->lock);

	rc = ahci_handle_port_पूर्णांकr(host, irq_masked);

	/* HOST_IRQ_STAT behaves as level triggered latch meaning that
	 * it should be cleared after all the port events are cleared;
	 * otherwise, it will उठाओ a spurious पूर्णांकerrupt after each
	 * valid one.  Please पढ़ो section 10.6.2 of ahci 1.1 क्रम more
	 * inक्रमmation.
	 *
	 * Also, use the unmasked value to clear पूर्णांकerrupt as spurious
	 * pending event on a dummy port might cause screaming IRQ.
	 */
	ग_लिखोl(irq_stat, mmio + HOST_IRQ_STAT);

	spin_unlock(&host->lock);

	VPRINTK("EXIT\n");

	वापस IRQ_RETVAL(rc);
पूर्ण

अचिन्हित पूर्णांक ahci_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	काष्ठा ahci_port_priv *pp = ap->निजी_data;

	/* Keep track of the currently active link.  It will be used
	 * in completion path to determine whether NCQ phase is in
	 * progress.
	 */
	pp->active_link = qc->dev->link;

	अगर (ata_is_ncq(qc->tf.protocol))
		ग_लिखोl(1 << qc->hw_tag, port_mmio + PORT_SCR_ACT);

	अगर (pp->fbs_enabled && pp->fbs_last_dev != qc->dev->link->pmp) अणु
		u32 fbs = पढ़ोl(port_mmio + PORT_FBS);
		fbs &= ~(PORT_FBS_DEV_MASK | PORT_FBS_DEC);
		fbs |= qc->dev->link->pmp << PORT_FBS_DEV_OFFSET;
		ग_लिखोl(fbs, port_mmio + PORT_FBS);
		pp->fbs_last_dev = qc->dev->link->pmp;
	पूर्ण

	ग_लिखोl(1 << qc->hw_tag, port_mmio + PORT_CMD_ISSUE);

	ahci_sw_activity(qc->dev->link);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_qc_issue);

अटल bool ahci_qc_fill_rtf(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ahci_port_priv *pp = qc->ap->निजी_data;
	u8 *rx_fis = pp->rx_fis;

	अगर (pp->fbs_enabled)
		rx_fis += qc->dev->link->pmp * AHCI_RX_FIS_SZ;

	/*
	 * After a successful execution of an ATA PIO data-in command,
	 * the device करोesn't send D2H Reg FIS to update the TF and
	 * the host should take TF and E_Status from the preceding PIO
	 * Setup FIS.
	 */
	अगर (qc->tf.protocol == ATA_PROT_PIO && qc->dma_dir == DMA_FROM_DEVICE &&
	    !(qc->flags & ATA_QCFLAG_FAILED)) अणु
		ata_tf_from_fis(rx_fis + RX_FIS_PIO_SETUP, &qc->result_tf);
		qc->result_tf.command = (rx_fis + RX_FIS_PIO_SETUP)[15];
	पूर्ण अन्यथा
		ata_tf_from_fis(rx_fis + RX_FIS_D2H_REG, &qc->result_tf);

	वापस true;
पूर्ण

अटल व्योम ahci_मुक्तze(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(ap);

	/* turn IRQ off */
	ग_लिखोl(0, port_mmio + PORT_IRQ_MASK);
पूर्ण

अटल व्योम ahci_thaw(काष्ठा ata_port *ap)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 पंचांगp;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;

	/* clear IRQ */
	पंचांगp = पढ़ोl(port_mmio + PORT_IRQ_STAT);
	ग_लिखोl(पंचांगp, port_mmio + PORT_IRQ_STAT);
	ग_लिखोl(1 << ap->port_no, mmio + HOST_IRQ_STAT);

	/* turn IRQ back on */
	ग_लिखोl(pp->पूर्णांकr_mask, port_mmio + PORT_IRQ_MASK);
पूर्ण

व्योम ahci_error_handler(काष्ठा ata_port *ap)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;

	अगर (!(ap->pflags & ATA_PFLAG_FROZEN)) अणु
		/* restart engine */
		hpriv->stop_engine(ap);
		hpriv->start_engine(ap);
	पूर्ण

	sata_pmp_error_handler(ap);

	अगर (!ata_dev_enabled(ap->link.device))
		hpriv->stop_engine(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_error_handler);

अटल व्योम ahci_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;

	/* make DMA engine क्रमget about the failed command */
	अगर (qc->flags & ATA_QCFLAG_FAILED)
		ahci_kick_engine(ap);
पूर्ण

अटल व्योम ahci_set_aggressive_devslp(काष्ठा ata_port *ap, bool sleep)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	काष्ठा ata_device *dev = ap->link.device;
	u32 devslp, dm, dito, mdat, deto, dito_conf;
	पूर्णांक rc;
	अचिन्हित पूर्णांक err_mask;

	devslp = पढ़ोl(port_mmio + PORT_DEVSLP);
	अगर (!(devslp & PORT_DEVSLP_DSP)) अणु
		dev_info(ap->host->dev, "port does not support device sleep\n");
		वापस;
	पूर्ण

	/* disable device sleep */
	अगर (!sleep) अणु
		अगर (devslp & PORT_DEVSLP_ADSE) अणु
			ग_लिखोl(devslp & ~PORT_DEVSLP_ADSE,
			       port_mmio + PORT_DEVSLP);
			err_mask = ata_dev_set_feature(dev,
						       SETFEATURES_SATA_DISABLE,
						       SATA_DEVSLP);
			अगर (err_mask && err_mask != AC_ERR_DEV)
				ata_dev_warn(dev, "failed to disable DEVSLP\n");
		पूर्ण
		वापस;
	पूर्ण

	dm = (devslp & PORT_DEVSLP_DM_MASK) >> PORT_DEVSLP_DM_OFFSET;
	dito = devslp_idle_समयout / (dm + 1);
	अगर (dito > 0x3ff)
		dito = 0x3ff;

	dito_conf = (devslp >> PORT_DEVSLP_DITO_OFFSET) & 0x3FF;

	/* device sleep was alपढ़ोy enabled and same dito */
	अगर ((devslp & PORT_DEVSLP_ADSE) && (dito_conf == dito))
		वापस;

	/* set DITO, MDAT, DETO and enable DevSlp, need to stop engine first */
	rc = hpriv->stop_engine(ap);
	अगर (rc)
		वापस;

	/* Use the nominal value 10 ms अगर the पढ़ो MDAT is zero,
	 * the nominal value of DETO is 20 ms.
	 */
	अगर (dev->devslp_timing[ATA_LOG_DEVSLP_VALID] &
	    ATA_LOG_DEVSLP_VALID_MASK) अणु
		mdat = dev->devslp_timing[ATA_LOG_DEVSLP_MDAT] &
		       ATA_LOG_DEVSLP_MDAT_MASK;
		अगर (!mdat)
			mdat = 10;
		deto = dev->devslp_timing[ATA_LOG_DEVSLP_DETO];
		अगर (!deto)
			deto = 20;
	पूर्ण अन्यथा अणु
		mdat = 10;
		deto = 20;
	पूर्ण

	/* Make dito, mdat, deto bits to 0s */
	devslp &= ~GENMASK_ULL(24, 2);
	devslp |= ((dito << PORT_DEVSLP_DITO_OFFSET) |
		   (mdat << PORT_DEVSLP_MDAT_OFFSET) |
		   (deto << PORT_DEVSLP_DETO_OFFSET) |
		   PORT_DEVSLP_ADSE);
	ग_लिखोl(devslp, port_mmio + PORT_DEVSLP);

	hpriv->start_engine(ap);

	/* enable device sleep feature क्रम the drive */
	err_mask = ata_dev_set_feature(dev,
				       SETFEATURES_SATA_ENABLE,
				       SATA_DEVSLP);
	अगर (err_mask && err_mask != AC_ERR_DEV)
		ata_dev_warn(dev, "failed to enable DEVSLP\n");
पूर्ण

अटल व्योम ahci_enable_fbs(काष्ठा ata_port *ap)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 fbs;
	पूर्णांक rc;

	अगर (!pp->fbs_supported)
		वापस;

	fbs = पढ़ोl(port_mmio + PORT_FBS);
	अगर (fbs & PORT_FBS_EN) अणु
		pp->fbs_enabled = true;
		pp->fbs_last_dev = -1; /* initialization */
		वापस;
	पूर्ण

	rc = hpriv->stop_engine(ap);
	अगर (rc)
		वापस;

	ग_लिखोl(fbs | PORT_FBS_EN, port_mmio + PORT_FBS);
	fbs = पढ़ोl(port_mmio + PORT_FBS);
	अगर (fbs & PORT_FBS_EN) अणु
		dev_info(ap->host->dev, "FBS is enabled\n");
		pp->fbs_enabled = true;
		pp->fbs_last_dev = -1; /* initialization */
	पूर्ण अन्यथा
		dev_err(ap->host->dev, "Failed to enable FBS\n");

	hpriv->start_engine(ap);
पूर्ण

अटल व्योम ahci_disable_fbs(काष्ठा ata_port *ap)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 fbs;
	पूर्णांक rc;

	अगर (!pp->fbs_supported)
		वापस;

	fbs = पढ़ोl(port_mmio + PORT_FBS);
	अगर ((fbs & PORT_FBS_EN) == 0) अणु
		pp->fbs_enabled = false;
		वापस;
	पूर्ण

	rc = hpriv->stop_engine(ap);
	अगर (rc)
		वापस;

	ग_लिखोl(fbs & ~PORT_FBS_EN, port_mmio + PORT_FBS);
	fbs = पढ़ोl(port_mmio + PORT_FBS);
	अगर (fbs & PORT_FBS_EN)
		dev_err(ap->host->dev, "Failed to disable FBS\n");
	अन्यथा अणु
		dev_info(ap->host->dev, "FBS is disabled\n");
		pp->fbs_enabled = false;
	पूर्ण

	hpriv->start_engine(ap);
पूर्ण

अटल व्योम ahci_pmp_attach(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	u32 cmd;

	cmd = पढ़ोl(port_mmio + PORT_CMD);
	cmd |= PORT_CMD_PMP;
	ग_लिखोl(cmd, port_mmio + PORT_CMD);

	ahci_enable_fbs(ap);

	pp->पूर्णांकr_mask |= PORT_IRQ_BAD_PMP;

	/*
	 * We must not change the port पूर्णांकerrupt mask रेजिस्टर अगर the
	 * port is marked frozen, the value in pp->पूर्णांकr_mask will be
	 * restored later when the port is thawed.
	 *
	 * Note that during initialization, the port is marked as
	 * frozen since the irq handler is not yet रेजिस्टरed.
	 */
	अगर (!(ap->pflags & ATA_PFLAG_FROZEN))
		ग_लिखोl(pp->पूर्णांकr_mask, port_mmio + PORT_IRQ_MASK);
पूर्ण

अटल व्योम ahci_pmp_detach(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	u32 cmd;

	ahci_disable_fbs(ap);

	cmd = पढ़ोl(port_mmio + PORT_CMD);
	cmd &= ~PORT_CMD_PMP;
	ग_लिखोl(cmd, port_mmio + PORT_CMD);

	pp->पूर्णांकr_mask &= ~PORT_IRQ_BAD_PMP;

	/* see comment above in ahci_pmp_attach() */
	अगर (!(ap->pflags & ATA_PFLAG_FROZEN))
		ग_लिखोl(pp->पूर्णांकr_mask, port_mmio + PORT_IRQ_MASK);
पूर्ण

पूर्णांक ahci_port_resume(काष्ठा ata_port *ap)
अणु
	ahci_rpm_get_port(ap);

	ahci_घातer_up(ap);
	ahci_start_port(ap);

	अगर (sata_pmp_attached(ap))
		ahci_pmp_attach(ap);
	अन्यथा
		ahci_pmp_detach(ap);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_port_resume);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ahci_port_suspend(काष्ठा ata_port *ap, pm_message_t mesg)
अणु
	स्थिर अक्षर *emsg = शून्य;
	पूर्णांक rc;

	rc = ahci_deinit_port(ap, &emsg);
	अगर (rc == 0)
		ahci_घातer_करोwn(ap);
	अन्यथा अणु
		ata_port_err(ap, "%s (%d)\n", emsg, rc);
		ata_port_मुक्तze(ap);
	पूर्ण

	ahci_rpm_put_port(ap);
	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ahci_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा device *dev = ap->host->dev;
	काष्ठा ahci_port_priv *pp;
	व्योम *mem;
	dma_addr_t mem_dma;
	माप_प्रकार dma_sz, rx_fis_sz;

	pp = devm_kzalloc(dev, माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;

	अगर (ap->host->n_ports > 1) अणु
		pp->irq_desc = devm_kzalloc(dev, 8, GFP_KERNEL);
		अगर (!pp->irq_desc) अणु
			devm_kमुक्त(dev, pp);
			वापस -ENOMEM;
		पूर्ण
		snम_लिखो(pp->irq_desc, 8,
			 "%s%d", dev_driver_string(dev), ap->port_no);
	पूर्ण

	/* check FBS capability */
	अगर ((hpriv->cap & HOST_CAP_FBS) && sata_pmp_supported(ap)) अणु
		व्योम __iomem *port_mmio = ahci_port_base(ap);
		u32 cmd = पढ़ोl(port_mmio + PORT_CMD);
		अगर (cmd & PORT_CMD_FBSCP)
			pp->fbs_supported = true;
		अन्यथा अगर (hpriv->flags & AHCI_HFLAG_YES_FBS) अणु
			dev_info(dev, "port %d can do FBS, forcing FBSCP\n",
				 ap->port_no);
			pp->fbs_supported = true;
		पूर्ण अन्यथा
			dev_warn(dev, "port %d is not capable of FBS\n",
				 ap->port_no);
	पूर्ण

	अगर (pp->fbs_supported) अणु
		dma_sz = AHCI_PORT_PRIV_FBS_DMA_SZ;
		rx_fis_sz = AHCI_RX_FIS_SZ * 16;
	पूर्ण अन्यथा अणु
		dma_sz = AHCI_PORT_PRIV_DMA_SZ;
		rx_fis_sz = AHCI_RX_FIS_SZ;
	पूर्ण

	mem = dmam_alloc_coherent(dev, dma_sz, &mem_dma, GFP_KERNEL);
	अगर (!mem)
		वापस -ENOMEM;

	/*
	 * First item in chunk of DMA memory: 32-slot command table,
	 * 32 bytes each in size
	 */
	pp->cmd_slot = mem;
	pp->cmd_slot_dma = mem_dma;

	mem += AHCI_CMD_SLOT_SZ;
	mem_dma += AHCI_CMD_SLOT_SZ;

	/*
	 * Second item: Received-FIS area
	 */
	pp->rx_fis = mem;
	pp->rx_fis_dma = mem_dma;

	mem += rx_fis_sz;
	mem_dma += rx_fis_sz;

	/*
	 * Third item: data area क्रम storing a single command
	 * and its scatter-gather table
	 */
	pp->cmd_tbl = mem;
	pp->cmd_tbl_dma = mem_dma;

	/*
	 * Save off initial list of पूर्णांकerrupts to be enabled.
	 * This could be changed later
	 */
	pp->पूर्णांकr_mask = DEF_PORT_IRQ;

	/*
	 * Switch to per-port locking in हाल each port has its own MSI vector.
	 */
	अगर (hpriv->flags & AHCI_HFLAG_MULTI_MSI) अणु
		spin_lock_init(&pp->lock);
		ap->lock = &pp->lock;
	पूर्ण

	ap->निजी_data = pp;

	/* engage engines, captain */
	वापस ahci_port_resume(ap);
पूर्ण

अटल व्योम ahci_port_stop(काष्ठा ata_port *ap)
अणु
	स्थिर अक्षर *emsg = शून्य;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	व्योम __iomem *host_mmio = hpriv->mmio;
	पूर्णांक rc;

	/* de-initialize port */
	rc = ahci_deinit_port(ap, &emsg);
	अगर (rc)
		ata_port_warn(ap, "%s (%d)\n", emsg, rc);

	/*
	 * Clear GHC.IS to prevent stuck INTx after disabling MSI and
	 * re-enabling INTx.
	 */
	ग_लिखोl(1 << ap->port_no, host_mmio + HOST_IRQ_STAT);

	ahci_rpm_put_port(ap);
पूर्ण

व्योम ahci_prपूर्णांक_info(काष्ठा ata_host *host, स्थिर अक्षर *scc_s)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	u32 vers, cap, cap2, impl, speed;
	स्थिर अक्षर *speed_s;

	vers = hpriv->version;
	cap = hpriv->cap;
	cap2 = hpriv->cap2;
	impl = hpriv->port_map;

	speed = (cap >> 20) & 0xf;
	अगर (speed == 1)
		speed_s = "1.5";
	अन्यथा अगर (speed == 2)
		speed_s = "3";
	अन्यथा अगर (speed == 3)
		speed_s = "6";
	अन्यथा
		speed_s = "?";

	dev_info(host->dev,
		"AHCI %02x%02x.%02x%02x "
		"%u slots %u ports %s Gbps 0x%x impl %s mode\n"
		,

		(vers >> 24) & 0xff,
		(vers >> 16) & 0xff,
		(vers >> 8) & 0xff,
		vers & 0xff,

		((cap >> 8) & 0x1f) + 1,
		(cap & 0x1f) + 1,
		speed_s,
		impl,
		scc_s);

	dev_info(host->dev,
		"flags: "
		"%s%s%s%s%s%s%s"
		"%s%s%s%s%s%s%s"
		"%s%s%s%s%s%s%s"
		"%s%s\n"
		,

		cap & HOST_CAP_64 ? "64bit " : "",
		cap & HOST_CAP_NCQ ? "ncq " : "",
		cap & HOST_CAP_SNTF ? "sntf " : "",
		cap & HOST_CAP_MPS ? "ilck " : "",
		cap & HOST_CAP_SSS ? "stag " : "",
		cap & HOST_CAP_ALPM ? "pm " : "",
		cap & HOST_CAP_LED ? "led " : "",
		cap & HOST_CAP_CLO ? "clo " : "",
		cap & HOST_CAP_ONLY ? "only " : "",
		cap & HOST_CAP_PMP ? "pmp " : "",
		cap & HOST_CAP_FBS ? "fbs " : "",
		cap & HOST_CAP_PIO_MULTI ? "pio " : "",
		cap & HOST_CAP_SSC ? "slum " : "",
		cap & HOST_CAP_PART ? "part " : "",
		cap & HOST_CAP_CCC ? "ccc " : "",
		cap & HOST_CAP_EMS ? "ems " : "",
		cap & HOST_CAP_SXS ? "sxs " : "",
		cap2 & HOST_CAP2_DESO ? "deso " : "",
		cap2 & HOST_CAP2_SADM ? "sadm " : "",
		cap2 & HOST_CAP2_SDS ? "sds " : "",
		cap2 & HOST_CAP2_APST ? "apst " : "",
		cap2 & HOST_CAP2_NVMHCI ? "nvmp " : "",
		cap2 & HOST_CAP2_BOH ? "boh " : ""
		);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_prपूर्णांक_info);

व्योम ahci_set_em_messages(काष्ठा ahci_host_priv *hpriv,
			  काष्ठा ata_port_info *pi)
अणु
	u8 messages;
	व्योम __iomem *mmio = hpriv->mmio;
	u32 em_loc = पढ़ोl(mmio + HOST_EM_LOC);
	u32 em_ctl = पढ़ोl(mmio + HOST_EM_CTL);

	अगर (!ahci_em_messages || !(hpriv->cap & HOST_CAP_EMS))
		वापस;

	messages = (em_ctl & EM_CTRL_MSG_TYPE) >> 16;

	अगर (messages) अणु
		/* store em_loc */
		hpriv->em_loc = ((em_loc >> 16) * 4);
		hpriv->em_buf_sz = ((em_loc & 0xff) * 4);
		hpriv->em_msg_type = messages;
		pi->flags |= ATA_FLAG_EM;
		अगर (!(em_ctl & EM_CTL_ALHD))
			pi->flags |= ATA_FLAG_SW_ACTIVITY;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ahci_set_em_messages);

अटल पूर्णांक ahci_host_activate_multi_irqs(काष्ठा ata_host *host,
					 काष्ठा scsi_host_ढाँचा *sht)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	पूर्णांक i, rc;

	rc = ata_host_start(host);
	अगर (rc)
		वापस rc;
	/*
	 * Requests IRQs according to AHCI-1.1 when multiple MSIs were
	 * allocated. That is one MSI per port, starting from @irq.
	 */
	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ahci_port_priv *pp = host->ports[i]->निजी_data;
		पूर्णांक irq = hpriv->get_irq_vector(host, i);

		/* Do not receive पूर्णांकerrupts sent by dummy ports */
		अगर (!pp) अणु
			disable_irq(irq);
			जारी;
		पूर्ण

		rc = devm_request_irq(host->dev, irq, ahci_multi_irqs_पूर्णांकr_hard,
				0, pp->irq_desc, host->ports[i]);

		अगर (rc)
			वापस rc;
		ata_port_desc(host->ports[i], "irq %d", irq);
	पूर्ण

	वापस ata_host_रेजिस्टर(host, sht);
पूर्ण

/**
 *	ahci_host_activate - start AHCI host, request IRQs and रेजिस्टर it
 *	@host: target ATA host
 *	@sht: scsi_host_ढाँचा to use when रेजिस्टरing the host
 *
 *	LOCKING:
 *	Inherited from calling layer (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ahci_host_activate(काष्ठा ata_host *host, काष्ठा scsi_host_ढाँचा *sht)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	पूर्णांक irq = hpriv->irq;
	पूर्णांक rc;

	अगर (hpriv->flags & AHCI_HFLAG_MULTI_MSI) अणु
		अगर (hpriv->irq_handler &&
		    hpriv->irq_handler != ahci_single_level_irq_पूर्णांकr)
			dev_warn(host->dev,
			         "both AHCI_HFLAG_MULTI_MSI flag set and custom irq handler implemented\n");
		अगर (!hpriv->get_irq_vector) अणु
			dev_err(host->dev,
				"AHCI_HFLAG_MULTI_MSI requires ->get_irq_vector!\n");
			वापस -EIO;
		पूर्ण

		rc = ahci_host_activate_multi_irqs(host, sht);
	पूर्ण अन्यथा अणु
		rc = ata_host_activate(host, irq, hpriv->irq_handler,
				       IRQF_SHARED, sht);
	पूर्ण


	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_host_activate);

MODULE_AUTHOR("Jeff Garzik");
MODULE_DESCRIPTION("Common AHCI SATA low-level routines");
MODULE_LICENSE("GPL");
