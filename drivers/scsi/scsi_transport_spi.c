<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* 
 *  Parallel SCSI (SPI) transport specअगरic attributes exported to sysfs.
 *
 *  Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.
 *  Copyright (c) 2004, 2005 James Bottomley <James.Bottomley@SteelEye.com>
 */
#समावेश <linux/प्रकार.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश <scsi/scsi.h>
#समावेश "scsi_priv.h"
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_spi.h>

#घोषणा SPI_NUM_ATTRS 14	/* increase this अगर you add attributes */
#घोषणा SPI_OTHER_ATTRS 1	/* Increase this अगर you add "always
				 * on" attributes */
#घोषणा SPI_HOST_ATTRS	1

#घोषणा SPI_MAX_ECHO_BUFFER_SIZE	4096

#घोषणा DV_LOOPS	3
#घोषणा DV_TIMEOUT	(10*HZ)
#घोषणा DV_RETRIES	3	/* should only need at most 
				 * two cc/ua clears */

/* Our blacklist flags */
क्रमागत अणु
	SPI_BLIST_NOIUS = (__क्रमce blist_flags_t)0x1,
पूर्ण;

/* blacklist table, modelled on scsi_devinfo.c */
अटल काष्ठा अणु
	अक्षर *venकरोr;
	अक्षर *model;
	blist_flags_t flags;
पूर्ण spi_अटल_device_list[] __initdata = अणु
	अणु"HP", "Ultrium 3-SCSI", SPI_BLIST_NOIUS पूर्ण,
	अणु"IBM", "ULTRIUM-TD3", SPI_BLIST_NOIUS पूर्ण,
	अणुशून्य, शून्य, 0पूर्ण
पूर्ण;

/* Private data accessors (keep these out of the header file) */
#घोषणा spi_dv_in_progress(x) (((काष्ठा spi_transport_attrs *)&(x)->starget_data)->dv_in_progress)
#घोषणा spi_dv_mutex(x) (((काष्ठा spi_transport_attrs *)&(x)->starget_data)->dv_mutex)

काष्ठा spi_पूर्णांकernal अणु
	काष्ठा scsi_transport_ढाँचा t;
	काष्ठा spi_function_ढाँचा *f;
पूर्ण;

#घोषणा to_spi_पूर्णांकernal(पंचांगpl)	container_of(पंचांगpl, काष्ठा spi_पूर्णांकernal, t)

अटल स्थिर पूर्णांक ppr_to_ps[] = अणु
	/* The PPR values 0-6 are reserved, fill them in when
	 * the committee defines them */
	-1,			/* 0x00 */
	-1,			/* 0x01 */
	-1,			/* 0x02 */
	-1,			/* 0x03 */
	-1,			/* 0x04 */
	-1,			/* 0x05 */
	-1,			/* 0x06 */
	 3125,			/* 0x07 */
	 6250,			/* 0x08 */
	12500,			/* 0x09 */
	25000,			/* 0x0a */
	30300,			/* 0x0b */
	50000,			/* 0x0c */
पूर्ण;
/* The PPR values at which you calculate the period in ns by multiplying
 * by 4 */
#घोषणा SPI_STATIC_PPR	0x0c

अटल पूर्णांक sprपूर्णांक_frac(अक्षर *dest, पूर्णांक value, पूर्णांक denom)
अणु
	पूर्णांक frac = value % denom;
	पूर्णांक result = प्र_लिखो(dest, "%d", value / denom);

	अगर (frac == 0)
		वापस result;
	dest[result++] = '.';

	करो अणु
		denom /= 10;
		प्र_लिखो(dest + result, "%d", frac / denom);
		result++;
		frac %= denom;
	पूर्ण जबतक (frac);

	dest[result++] = '\0';
	वापस result;
पूर्ण

अटल पूर्णांक spi_execute(काष्ठा scsi_device *sdev, स्थिर व्योम *cmd,
		       क्रमागत dma_data_direction dir,
		       व्योम *buffer, अचिन्हित bufflen,
		       काष्ठा scsi_sense_hdr *sshdr)
अणु
	पूर्णांक i, result;
	अचिन्हित अक्षर sense[SCSI_SENSE_BUFFERSIZE];
	काष्ठा scsi_sense_hdr sshdr_पंचांगp;

	अगर (!sshdr)
		sshdr = &sshdr_पंचांगp;

	क्रम(i = 0; i < DV_RETRIES; i++) अणु
		/*
		 * The purpose of the RQF_PM flag below is to bypass the
		 * SDEV_QUIESCE state.
		 */
		result = scsi_execute(sdev, cmd, dir, buffer, bufflen, sense,
				      sshdr, DV_TIMEOUT, /* retries */ 1,
				      REQ_FAILFAST_DEV |
				      REQ_FAILFAST_TRANSPORT |
				      REQ_FAILFAST_DRIVER,
				      RQF_PM, शून्य);
		अगर (driver_byte(result) != DRIVER_SENSE ||
		    sshdr->sense_key != UNIT_ATTENTION)
			अवरोध;
	पूर्ण
	वापस result;
पूर्ण

अटल काष्ठा अणु
	क्रमागत spi_संकेत_type	value;
	अक्षर			*name;
पूर्ण संकेत_types[] = अणु
	अणु SPI_SIGNAL_UNKNOWN, "unknown" पूर्ण,
	अणु SPI_SIGNAL_SE, "SE" पूर्ण,
	अणु SPI_SIGNAL_LVD, "LVD" पूर्ण,
	अणु SPI_SIGNAL_HVD, "HVD" पूर्ण,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *spi_संकेत_to_string(क्रमागत spi_संकेत_type type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(संकेत_types); i++) अणु
		अगर (type == संकेत_types[i].value)
			वापस संकेत_types[i].name;
	पूर्ण
	वापस शून्य;
पूर्ण
अटल अंतरभूत क्रमागत spi_संकेत_type spi_संकेत_to_value(स्थिर अक्षर *name)
अणु
	पूर्णांक i, len;

	क्रम (i = 0; i < ARRAY_SIZE(संकेत_types); i++) अणु
		len =  म_माप(संकेत_types[i].name);
		अगर (म_भेदन(name, संकेत_types[i].name, len) == 0 &&
		    (name[len] == '\n' || name[len] == '\0'))
			वापस संकेत_types[i].value;
	पूर्ण
	वापस SPI_SIGNAL_UNKNOWN;
पूर्ण

अटल पूर्णांक spi_host_setup(काष्ठा transport_container *tc, काष्ठा device *dev,
			  काष्ठा device *cdev)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(dev);

	spi_संकेतling(shost) = SPI_SIGNAL_UNKNOWN;

	वापस 0;
पूर्ण

अटल पूर्णांक spi_host_configure(काष्ठा transport_container *tc,
			      काष्ठा device *dev,
			      काष्ठा device *cdev);

अटल DECLARE_TRANSPORT_CLASS(spi_host_class,
			       "spi_host",
			       spi_host_setup,
			       शून्य,
			       spi_host_configure);

अटल पूर्णांक spi_host_match(काष्ठा attribute_container *cont,
			  काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;

	अगर (!scsi_is_host_device(dev))
		वापस 0;

	shost = dev_to_shost(dev);
	अगर (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &spi_host_class.class)
		वापस 0;

	वापस &shost->transportt->host_attrs.ac == cont;
पूर्ण

अटल पूर्णांक spi_target_configure(काष्ठा transport_container *tc,
				काष्ठा device *dev,
				काष्ठा device *cdev);

अटल पूर्णांक spi_device_configure(काष्ठा transport_container *tc,
				काष्ठा device *dev,
				काष्ठा device *cdev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा scsi_target *starget = sdev->sdev_target;
	blist_flags_t bflags;

	bflags = scsi_get_device_flags_keyed(sdev, &sdev->inquiry[8],
					     &sdev->inquiry[16],
					     SCSI_DEVINFO_SPI);

	/* Populate the target capability fields with the values
	 * gleaned from the device inquiry */

	spi_support_sync(starget) = scsi_device_sync(sdev);
	spi_support_wide(starget) = scsi_device_wide(sdev);
	spi_support_dt(starget) = scsi_device_dt(sdev);
	spi_support_dt_only(starget) = scsi_device_dt_only(sdev);
	spi_support_ius(starget) = scsi_device_ius(sdev);
	अगर (bflags & SPI_BLIST_NOIUS) अणु
		dev_info(dev, "Information Units disabled by blacklist\n");
		spi_support_ius(starget) = 0;
	पूर्ण
	spi_support_qas(starget) = scsi_device_qas(sdev);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_setup_transport_attrs(काष्ठा transport_container *tc,
				     काष्ठा device *dev,
				     काष्ठा device *cdev)
अणु
	काष्ठा scsi_target *starget = to_scsi_target(dev);

	spi_period(starget) = -1;	/* illegal value */
	spi_min_period(starget) = 0;
	spi_offset(starget) = 0;	/* async */
	spi_max_offset(starget) = 255;
	spi_width(starget) = 0;	/* narrow */
	spi_max_width(starget) = 1;
	spi_iu(starget) = 0;	/* no IU */
	spi_max_iu(starget) = 1;
	spi_dt(starget) = 0;	/* ST */
	spi_qas(starget) = 0;
	spi_max_qas(starget) = 1;
	spi_wr_flow(starget) = 0;
	spi_rd_strm(starget) = 0;
	spi_rti(starget) = 0;
	spi_pcomp_en(starget) = 0;
	spi_hold_mcs(starget) = 0;
	spi_dv_pending(starget) = 0;
	spi_dv_in_progress(starget) = 0;
	spi_initial_dv(starget) = 0;
	mutex_init(&spi_dv_mutex(starget));

	वापस 0;
पूर्ण

#घोषणा spi_transport_show_simple(field, क्रमmat_string)			\
									\
अटल sमाप_प्रकार								\
show_spi_transport_##field(काष्ठा device *dev, 			\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा scsi_target *starget = transport_class_to_starget(dev);	\
	काष्ठा spi_transport_attrs *tp;					\
									\
	tp = (काष्ठा spi_transport_attrs *)&starget->starget_data;	\
	वापस snम_लिखो(buf, 20, क्रमmat_string, tp->field);		\
पूर्ण

#घोषणा spi_transport_store_simple(field, क्रमmat_string)		\
									\
अटल sमाप_प्रकार								\
store_spi_transport_##field(काष्ठा device *dev, 			\
			    काष्ठा device_attribute *attr, 		\
			    स्थिर अक्षर *buf, माप_प्रकार count)		\
अणु									\
	पूर्णांक val;							\
	काष्ठा scsi_target *starget = transport_class_to_starget(dev);	\
	काष्ठा spi_transport_attrs *tp;					\
									\
	tp = (काष्ठा spi_transport_attrs *)&starget->starget_data;	\
	val = simple_म_से_अदीर्घ(buf, शून्य, 0);				\
	tp->field = val;						\
	वापस count;							\
पूर्ण

#घोषणा spi_transport_show_function(field, क्रमmat_string)		\
									\
अटल sमाप_प्रकार								\
show_spi_transport_##field(काष्ठा device *dev, 			\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा scsi_target *starget = transport_class_to_starget(dev);	\
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);	\
	काष्ठा spi_transport_attrs *tp;					\
	काष्ठा spi_पूर्णांकernal *i = to_spi_पूर्णांकernal(shost->transportt);	\
	tp = (काष्ठा spi_transport_attrs *)&starget->starget_data;	\
	अगर (i->f->get_##field)						\
		i->f->get_##field(starget);				\
	वापस snम_लिखो(buf, 20, क्रमmat_string, tp->field);		\
पूर्ण

#घोषणा spi_transport_store_function(field, क्रमmat_string)		\
अटल sमाप_प्रकार								\
store_spi_transport_##field(काष्ठा device *dev, 			\
			    काष्ठा device_attribute *attr,		\
			    स्थिर अक्षर *buf, माप_प्रकार count)		\
अणु									\
	पूर्णांक val;							\
	काष्ठा scsi_target *starget = transport_class_to_starget(dev);	\
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);	\
	काष्ठा spi_पूर्णांकernal *i = to_spi_पूर्णांकernal(shost->transportt);	\
									\
	अगर (!i->f->set_##field)						\
		वापस -EINVAL;						\
	val = simple_म_से_अदीर्घ(buf, शून्य, 0);				\
	i->f->set_##field(starget, val);				\
	वापस count;							\
पूर्ण

#घोषणा spi_transport_store_max(field, क्रमmat_string)			\
अटल sमाप_प्रकार								\
store_spi_transport_##field(काष्ठा device *dev, 			\
			    काष्ठा device_attribute *attr,		\
			    स्थिर अक्षर *buf, माप_प्रकार count)		\
अणु									\
	पूर्णांक val;							\
	काष्ठा scsi_target *starget = transport_class_to_starget(dev);	\
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);	\
	काष्ठा spi_पूर्णांकernal *i = to_spi_पूर्णांकernal(shost->transportt);	\
	काष्ठा spi_transport_attrs *tp					\
		= (काष्ठा spi_transport_attrs *)&starget->starget_data;	\
									\
	अगर (!i->f->set_##field)						\
		वापस -EINVAL;						\
	val = simple_म_से_अदीर्घ(buf, शून्य, 0);				\
	अगर (val > tp->max_##field)					\
		val = tp->max_##field;					\
	i->f->set_##field(starget, val);				\
	वापस count;							\
पूर्ण

#घोषणा spi_transport_rd_attr(field, क्रमmat_string)			\
	spi_transport_show_function(field, क्रमmat_string)		\
	spi_transport_store_function(field, क्रमmat_string)		\
अटल DEVICE_ATTR(field, S_IRUGO,				\
		   show_spi_transport_##field,			\
		   store_spi_transport_##field);

#घोषणा spi_transport_simple_attr(field, क्रमmat_string)			\
	spi_transport_show_simple(field, क्रमmat_string)			\
	spi_transport_store_simple(field, क्रमmat_string)		\
अटल DEVICE_ATTR(field, S_IRUGO,				\
		   show_spi_transport_##field,			\
		   store_spi_transport_##field);

#घोषणा spi_transport_max_attr(field, क्रमmat_string)			\
	spi_transport_show_function(field, क्रमmat_string)		\
	spi_transport_store_max(field, क्रमmat_string)			\
	spi_transport_simple_attr(max_##field, क्रमmat_string)		\
अटल DEVICE_ATTR(field, S_IRUGO,				\
		   show_spi_transport_##field,			\
		   store_spi_transport_##field);

/* The Parallel SCSI Tranport Attributes: */
spi_transport_max_attr(offset, "%d\n");
spi_transport_max_attr(width, "%d\n");
spi_transport_max_attr(iu, "%d\n");
spi_transport_rd_attr(dt, "%d\n");
spi_transport_max_attr(qas, "%d\n");
spi_transport_rd_attr(wr_flow, "%d\n");
spi_transport_rd_attr(rd_strm, "%d\n");
spi_transport_rd_attr(rti, "%d\n");
spi_transport_rd_attr(pcomp_en, "%d\n");
spi_transport_rd_attr(hold_mcs, "%d\n");

/* we only care about the first child device that's a real SCSI device
 * so we वापस 1 to terminate the iteration when we find it */
अटल पूर्णांक child_iter(काष्ठा device *dev, व्योम *data)
अणु
	अगर (!scsi_is_sdev_device(dev))
		वापस 0;

	spi_dv_device(to_scsi_device(dev));
	वापस 1;
पूर्ण

अटल sमाप_प्रकार
store_spi_revalidate(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_target *starget = transport_class_to_starget(dev);

	device_क्रम_each_child(&starget->dev, शून्य, child_iter);
	वापस count;
पूर्ण
अटल DEVICE_ATTR(revalidate, S_IWUSR, शून्य, store_spi_revalidate);

/* Translate the period पूर्णांकo ns according to the current spec
 * क्रम SDTR/PPR messages */
अटल पूर्णांक period_to_str(अक्षर *buf, पूर्णांक period)
अणु
	पूर्णांक len, picosec;

	अगर (period < 0 || period > 0xff) अणु
		picosec = -1;
	पूर्ण अन्यथा अगर (period <= SPI_STATIC_PPR) अणु
		picosec = ppr_to_ps[period];
	पूर्ण अन्यथा अणु
		picosec = period * 4000;
	पूर्ण

	अगर (picosec == -1) अणु
		len = प्र_लिखो(buf, "reserved");
	पूर्ण अन्यथा अणु
		len = sprपूर्णांक_frac(buf, picosec, 1000);
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार
show_spi_transport_period_helper(अक्षर *buf, पूर्णांक period)
अणु
	पूर्णांक len = period_to_str(buf, period);
	buf[len++] = '\n';
	buf[len] = '\0';
	वापस len;
पूर्ण

अटल sमाप_प्रकार
store_spi_transport_period_helper(काष्ठा device *dev, स्थिर अक्षर *buf,
				  माप_प्रकार count, पूर्णांक *periodp)
अणु
	पूर्णांक j, picosec, period = -1;
	अक्षर *endp;

	picosec = simple_म_से_अदीर्घ(buf, &endp, 10) * 1000;
	अगर (*endp == '.') अणु
		पूर्णांक mult = 100;
		करो अणु
			endp++;
			अगर (!है_अंक(*endp))
				अवरोध;
			picosec += (*endp - '0') * mult;
			mult /= 10;
		पूर्ण जबतक (mult > 0);
	पूर्ण

	क्रम (j = 0; j <= SPI_STATIC_PPR; j++) अणु
		अगर (ppr_to_ps[j] < picosec)
			जारी;
		period = j;
		अवरोध;
	पूर्ण

	अगर (period == -1)
		period = picosec / 4000;

	अगर (period > 0xff)
		period = 0xff;

	*periodp = period;

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_spi_transport_period(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_target *starget = transport_class_to_starget(dev);
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा spi_पूर्णांकernal *i = to_spi_पूर्णांकernal(shost->transportt);
	काष्ठा spi_transport_attrs *tp =
		(काष्ठा spi_transport_attrs *)&starget->starget_data;

	अगर (i->f->get_period)
		i->f->get_period(starget);

	वापस show_spi_transport_period_helper(buf, tp->period);
पूर्ण

अटल sमाप_प्रकार
store_spi_transport_period(काष्ठा device *cdev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_target *starget = transport_class_to_starget(cdev);
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा spi_पूर्णांकernal *i = to_spi_पूर्णांकernal(shost->transportt);
	काष्ठा spi_transport_attrs *tp =
		(काष्ठा spi_transport_attrs *)&starget->starget_data;
	पूर्णांक period, retval;

	अगर (!i->f->set_period)
		वापस -EINVAL;

	retval = store_spi_transport_period_helper(cdev, buf, count, &period);

	अगर (period < tp->min_period)
		period = tp->min_period;

	i->f->set_period(starget, period);

	वापस retval;
पूर्ण

अटल DEVICE_ATTR(period, S_IRUGO,
		   show_spi_transport_period,
		   store_spi_transport_period);

अटल sमाप_प्रकार
show_spi_transport_min_period(काष्ठा device *cdev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_target *starget = transport_class_to_starget(cdev);
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा spi_पूर्णांकernal *i = to_spi_पूर्णांकernal(shost->transportt);
	काष्ठा spi_transport_attrs *tp =
		(काष्ठा spi_transport_attrs *)&starget->starget_data;

	अगर (!i->f->set_period)
		वापस -EINVAL;

	वापस show_spi_transport_period_helper(buf, tp->min_period);
पूर्ण

अटल sमाप_प्रकार
store_spi_transport_min_period(काष्ठा device *cdev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_target *starget = transport_class_to_starget(cdev);
	काष्ठा spi_transport_attrs *tp =
		(काष्ठा spi_transport_attrs *)&starget->starget_data;

	वापस store_spi_transport_period_helper(cdev, buf, count,
						 &tp->min_period);
पूर्ण


अटल DEVICE_ATTR(min_period, S_IRUGO,
		   show_spi_transport_min_period,
		   store_spi_transport_min_period);


अटल sमाप_प्रकार show_spi_host_संकेतling(काष्ठा device *cdev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(cdev);
	काष्ठा spi_पूर्णांकernal *i = to_spi_पूर्णांकernal(shost->transportt);

	अगर (i->f->get_संकेतling)
		i->f->get_संकेतling(shost);

	वापस प्र_लिखो(buf, "%s\n", spi_संकेत_to_string(spi_संकेतling(shost)));
पूर्ण
अटल sमाप_प्रकार store_spi_host_संकेतling(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(dev);
	काष्ठा spi_पूर्णांकernal *i = to_spi_पूर्णांकernal(shost->transportt);
	क्रमागत spi_संकेत_type type = spi_संकेत_to_value(buf);

	अगर (!i->f->set_संकेतling)
		वापस -EINVAL;

	अगर (type != SPI_SIGNAL_UNKNOWN)
		i->f->set_संकेतling(shost, type);

	वापस count;
पूर्ण
अटल DEVICE_ATTR(संकेतling, S_IRUGO,
		   show_spi_host_संकेतling,
		   store_spi_host_संकेतling);

अटल sमाप_प्रकार show_spi_host_width(काष्ठा device *cdev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(cdev);

	वापस प्र_लिखो(buf, "%s\n", shost->max_id == 16 ? "wide" : "narrow");
पूर्ण
अटल DEVICE_ATTR(host_width, S_IRUGO,
		   show_spi_host_width, शून्य);

अटल sमाप_प्रकार show_spi_host_hba_id(काष्ठा device *cdev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = transport_class_to_shost(cdev);

	वापस प्र_लिखो(buf, "%d\n", shost->this_id);
पूर्ण
अटल DEVICE_ATTR(hba_id, S_IRUGO,
		   show_spi_host_hba_id, शून्य);

#घोषणा DV_SET(x, y)			\
	अगर(i->f->set_##x)		\
		i->f->set_##x(sdev->sdev_target, y)

क्रमागत spi_compare_वापसs अणु
	SPI_COMPARE_SUCCESS,
	SPI_COMPARE_FAILURE,
	SPI_COMPARE_SKIP_TEST,
पूर्ण;


/* This is क्रम पढ़ो/ग_लिखो Doमुख्य Validation:  If the device supports
 * an echo buffer, we करो पढ़ो/ग_लिखो tests to it */
अटल क्रमागत spi_compare_वापसs
spi_dv_device_echo_buffer(काष्ठा scsi_device *sdev, u8 *buffer,
			  u8 *ptr, स्थिर पूर्णांक retries)
अणु
	पूर्णांक len = ptr - buffer;
	पूर्णांक j, k, r, result;
	अचिन्हित पूर्णांक pattern = 0x0000ffff;
	काष्ठा scsi_sense_hdr sshdr;

	स्थिर अक्षर spi_ग_लिखो_buffer[] = अणु
		WRITE_BUFFER, 0x0a, 0, 0, 0, 0, 0, len >> 8, len & 0xff, 0
	पूर्ण;
	स्थिर अक्षर spi_पढ़ो_buffer[] = अणु
		READ_BUFFER, 0x0a, 0, 0, 0, 0, 0, len >> 8, len & 0xff, 0
	पूर्ण;

	/* set up the pattern buffer.  Doesn't matter अगर we spill
	 * slightly beyond since that's where the पढ़ो buffer is */
	क्रम (j = 0; j < len; ) अणु

		/* fill the buffer with counting (test a) */
		क्रम ( ; j < min(len, 32); j++)
			buffer[j] = j;
		k = j;
		/* fill the buffer with alternating words of 0x0 and
		 * 0xffff (test b) */
		क्रम ( ; j < min(len, k + 32); j += 2) अणु
			u16 *word = (u16 *)&buffer[j];
			
			*word = (j & 0x02) ? 0x0000 : 0xffff;
		पूर्ण
		k = j;
		/* fill with crosstalk (alternating 0x5555 0xaaa)
                 * (test c) */
		क्रम ( ; j < min(len, k + 32); j += 2) अणु
			u16 *word = (u16 *)&buffer[j];

			*word = (j & 0x02) ? 0x5555 : 0xaaaa;
		पूर्ण
		k = j;
		/* fill with shअगरting bits (test d) */
		क्रम ( ; j < min(len, k + 32); j += 4) अणु
			u32 *word = (अचिन्हित पूर्णांक *)&buffer[j];
			u32 roll = (pattern & 0x80000000) ? 1 : 0;
			
			*word = pattern;
			pattern = (pattern << 1) | roll;
		पूर्ण
		/* करोn't bother with अक्रमom data (test e) */
	पूर्ण

	क्रम (r = 0; r < retries; r++) अणु
		result = spi_execute(sdev, spi_ग_लिखो_buffer, DMA_TO_DEVICE,
				     buffer, len, &sshdr);
		अगर(result || !scsi_device_online(sdev)) अणु

			scsi_device_set_state(sdev, SDEV_QUIESCE);
			अगर (scsi_sense_valid(&sshdr)
			    && sshdr.sense_key == ILLEGAL_REQUEST
			    /* INVALID FIELD IN CDB */
			    && sshdr.asc == 0x24 && sshdr.ascq == 0x00)
				/* This would mean that the drive lied
				 * to us about supporting an echo
				 * buffer (unक्रमtunately some Western
				 * Digital drives करो precisely this)
				 */
				वापस SPI_COMPARE_SKIP_TEST;


			sdev_prपूर्णांकk(KERN_ERR, sdev, "Write Buffer failure %x\n", result);
			वापस SPI_COMPARE_FAILURE;
		पूर्ण

		स_रखो(ptr, 0, len);
		spi_execute(sdev, spi_पढ़ो_buffer, DMA_FROM_DEVICE,
			    ptr, len, शून्य);
		scsi_device_set_state(sdev, SDEV_QUIESCE);

		अगर (स_भेद(buffer, ptr, len) != 0)
			वापस SPI_COMPARE_FAILURE;
	पूर्ण
	वापस SPI_COMPARE_SUCCESS;
पूर्ण

/* This is क्रम the simplest क्रमm of Doमुख्य Validation: a पढ़ो test
 * on the inquiry data from the device */
अटल क्रमागत spi_compare_वापसs
spi_dv_device_compare_inquiry(काष्ठा scsi_device *sdev, u8 *buffer,
			      u8 *ptr, स्थिर पूर्णांक retries)
अणु
	पूर्णांक r, result;
	स्थिर पूर्णांक len = sdev->inquiry_len;
	स्थिर अक्षर spi_inquiry[] = अणु
		INQUIRY, 0, 0, 0, len, 0
	पूर्ण;

	क्रम (r = 0; r < retries; r++) अणु
		स_रखो(ptr, 0, len);

		result = spi_execute(sdev, spi_inquiry, DMA_FROM_DEVICE,
				     ptr, len, शून्य);
		
		अगर(result || !scsi_device_online(sdev)) अणु
			scsi_device_set_state(sdev, SDEV_QUIESCE);
			वापस SPI_COMPARE_FAILURE;
		पूर्ण

		/* If we करोn't have the inquiry data alपढ़ोy, the
		 * first पढ़ो माला_लो it */
		अगर (ptr == buffer) अणु
			ptr += len;
			--r;
			जारी;
		पूर्ण

		अगर (स_भेद(buffer, ptr, len) != 0)
			/* failure */
			वापस SPI_COMPARE_FAILURE;
	पूर्ण
	वापस SPI_COMPARE_SUCCESS;
पूर्ण

अटल क्रमागत spi_compare_वापसs
spi_dv_retrain(काष्ठा scsi_device *sdev, u8 *buffer, u8 *ptr,
	       क्रमागत spi_compare_वापसs 
	       (*compare_fn)(काष्ठा scsi_device *, u8 *, u8 *, पूर्णांक))
अणु
	काष्ठा spi_पूर्णांकernal *i = to_spi_पूर्णांकernal(sdev->host->transportt);
	काष्ठा scsi_target *starget = sdev->sdev_target;
	पूर्णांक period = 0, prevperiod = 0; 
	क्रमागत spi_compare_वापसs retval;


	क्रम (;;) अणु
		पूर्णांक newperiod;
		retval = compare_fn(sdev, buffer, ptr, DV_LOOPS);

		अगर (retval == SPI_COMPARE_SUCCESS
		    || retval == SPI_COMPARE_SKIP_TEST)
			अवरोध;

		/* OK, retrain, fallback */
		अगर (i->f->get_iu)
			i->f->get_iu(starget);
		अगर (i->f->get_qas)
			i->f->get_qas(starget);
		अगर (i->f->get_period)
			i->f->get_period(sdev->sdev_target);

		/* Here's the fallback sequence; first try turning off
		 * IU, then QAS (अगर we can control them), then finally
		 * fall करोwn the periods */
		अगर (i->f->set_iu && spi_iu(starget)) अणु
			starget_prपूर्णांकk(KERN_ERR, starget, "Domain Validation Disabling Information Units\n");
			DV_SET(iu, 0);
		पूर्ण अन्यथा अगर (i->f->set_qas && spi_qas(starget)) अणु
			starget_prपूर्णांकk(KERN_ERR, starget, "Domain Validation Disabling Quick Arbitration and Selection\n");
			DV_SET(qas, 0);
		पूर्ण अन्यथा अणु
			newperiod = spi_period(starget);
			period = newperiod > period ? newperiod : period;
			अगर (period < 0x0d)
				period++;
			अन्यथा
				period += period >> 1;

			अगर (unlikely(period > 0xff || period == prevperiod)) अणु
				/* Total failure; set to async and वापस */
				starget_prपूर्णांकk(KERN_ERR, starget, "Domain Validation Failure, dropping back to Asynchronous\n");
				DV_SET(offset, 0);
				वापस SPI_COMPARE_FAILURE;
			पूर्ण
			starget_prपूर्णांकk(KERN_ERR, starget, "Domain Validation detected failure, dropping back\n");
			DV_SET(period, period);
			prevperiod = period;
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक
spi_dv_device_get_echo_buffer(काष्ठा scsi_device *sdev, u8 *buffer)
अणु
	पूर्णांक l, result;

	/* first off करो a test unit पढ़ोy.  This can error out 
	 * because of reservations or some other reason.  If it
	 * fails, the device won't let us ग_लिखो to the echo buffer
	 * so just वापस failure */
	
	अटल स्थिर अक्षर spi_test_unit_पढ़ोy[] = अणु
		TEST_UNIT_READY, 0, 0, 0, 0, 0
	पूर्ण;

	अटल स्थिर अक्षर spi_पढ़ो_buffer_descriptor[] = अणु
		READ_BUFFER, 0x0b, 0, 0, 0, 0, 0, 0, 4, 0
	पूर्ण;

	
	/* We send a set of three TURs to clear any outstanding 
	 * unit attention conditions अगर they exist (Otherwise the
	 * buffer tests won't be happy).  If the TUR still fails
	 * (reservation conflict, device not पढ़ोy, etc) just
	 * skip the ग_लिखो tests */
	क्रम (l = 0; ; l++) अणु
		result = spi_execute(sdev, spi_test_unit_पढ़ोy, DMA_NONE, 
				     शून्य, 0, शून्य);

		अगर(result) अणु
			अगर(l >= 3)
				वापस 0;
		पूर्ण अन्यथा अणु
			/* TUR succeeded */
			अवरोध;
		पूर्ण
	पूर्ण

	result = spi_execute(sdev, spi_पढ़ो_buffer_descriptor, 
			     DMA_FROM_DEVICE, buffer, 4, शून्य);

	अगर (result)
		/* Device has no echo buffer */
		वापस 0;

	वापस buffer[3] + ((buffer[2] & 0x1f) << 8);
पूर्ण

अटल व्योम
spi_dv_device_पूर्णांकernal(काष्ठा scsi_device *sdev, u8 *buffer)
अणु
	काष्ठा spi_पूर्णांकernal *i = to_spi_पूर्णांकernal(sdev->host->transportt);
	काष्ठा scsi_target *starget = sdev->sdev_target;
	काष्ठा Scsi_Host *shost = sdev->host;
	पूर्णांक len = sdev->inquiry_len;
	पूर्णांक min_period = spi_min_period(starget);
	पूर्णांक max_width = spi_max_width(starget);
	/* first set us up क्रम narrow async */
	DV_SET(offset, 0);
	DV_SET(width, 0);

	अगर (spi_dv_device_compare_inquiry(sdev, buffer, buffer, DV_LOOPS)
	    != SPI_COMPARE_SUCCESS) अणु
		starget_prपूर्णांकk(KERN_ERR, starget, "Domain Validation Initial Inquiry Failed\n");
		/* FIXME: should probably offline the device here? */
		वापस;
	पूर्ण

	अगर (!spi_support_wide(starget)) अणु
		spi_max_width(starget) = 0;
		max_width = 0;
	पूर्ण

	/* test width */
	अगर (i->f->set_width && max_width) अणु
		i->f->set_width(starget, 1);

		अगर (spi_dv_device_compare_inquiry(sdev, buffer,
						   buffer + len,
						   DV_LOOPS)
		    != SPI_COMPARE_SUCCESS) अणु
			starget_prपूर्णांकk(KERN_ERR, starget, "Wide Transfers Fail\n");
			i->f->set_width(starget, 0);
			/* Make sure we करोn't क्रमce wide back on by asking
			 * क्रम a transfer period that requires it */
			max_width = 0;
			अगर (min_period < 10)
				min_period = 10;
		पूर्ण
	पूर्ण

	अगर (!i->f->set_period)
		वापस;

	/* device can't handle synchronous */
	अगर (!spi_support_sync(starget) && !spi_support_dt(starget))
		वापस;

	/* len == -1 is the संकेत that we need to ascertain the
	 * presence of an echo buffer beक्रमe trying to use it.  len ==
	 * 0 means we करोn't have an echo buffer */
	len = -1;

 retry:

	/* now set up to the maximum */
	DV_SET(offset, spi_max_offset(starget));
	DV_SET(period, min_period);

	/* try QAS requests; this should be harmless to set अगर the
	 * target supports it */
	अगर (spi_support_qas(starget) && spi_max_qas(starget)) अणु
		DV_SET(qas, 1);
	पूर्ण अन्यथा अणु
		DV_SET(qas, 0);
	पूर्ण

	अगर (spi_support_ius(starget) && spi_max_iu(starget) &&
	    min_period < 9) अणु
		/* This u320 (or u640). Set IU transfers */
		DV_SET(iu, 1);
		/* Then set the optional parameters */
		DV_SET(rd_strm, 1);
		DV_SET(wr_flow, 1);
		DV_SET(rti, 1);
		अगर (min_period == 8)
			DV_SET(pcomp_en, 1);
	पूर्ण अन्यथा अणु
		DV_SET(iu, 0);
	पूर्ण

	/* now that we've करोne all this, actually check the bus
	 * संकेत type (अगर known).  Some devices are stupid on
	 * a SE bus and still claim they can try LVD only settings */
	अगर (i->f->get_संकेतling)
		i->f->get_संकेतling(shost);
	अगर (spi_संकेतling(shost) == SPI_SIGNAL_SE ||
	    spi_संकेतling(shost) == SPI_SIGNAL_HVD ||
	    !spi_support_dt(starget)) अणु
		DV_SET(dt, 0);
	पूर्ण अन्यथा अणु
		DV_SET(dt, 1);
	पूर्ण
	/* set width last because it will pull all the other
	 * parameters करोwn to required values */
	DV_SET(width, max_width);

	/* Do the पढ़ो only INQUIRY tests */
	spi_dv_retrain(sdev, buffer, buffer + sdev->inquiry_len,
		       spi_dv_device_compare_inquiry);
	/* See अगर we actually managed to negotiate and sustain DT */
	अगर (i->f->get_dt)
		i->f->get_dt(starget);

	/* see अगर the device has an echo buffer.  If it करोes we can करो
	 * the SPI pattern ग_लिखो tests.  Because of some broken
	 * devices, we *only* try this on a device that has actually
	 * negotiated DT */

	अगर (len == -1 && spi_dt(starget))
		len = spi_dv_device_get_echo_buffer(sdev, buffer);

	अगर (len <= 0) अणु
		starget_prपूर्णांकk(KERN_INFO, starget, "Domain Validation skipping write tests\n");
		वापस;
	पूर्ण

	अगर (len > SPI_MAX_ECHO_BUFFER_SIZE) अणु
		starget_prपूर्णांकk(KERN_WARNING, starget, "Echo buffer size %d is too big, trimming to %d\n", len, SPI_MAX_ECHO_BUFFER_SIZE);
		len = SPI_MAX_ECHO_BUFFER_SIZE;
	पूर्ण

	अगर (spi_dv_retrain(sdev, buffer, buffer + len,
			   spi_dv_device_echo_buffer)
	    == SPI_COMPARE_SKIP_TEST) अणु
		/* OK, the stupid drive can't करो a ग_लिखो echo buffer
		 * test after all, fall back to the पढ़ो tests */
		len = 0;
		जाओ retry;
	पूर्ण
पूर्ण


/**	spi_dv_device - Do Doमुख्य Validation on the device
 *	@sdev:		scsi device to validate
 *
 *	Perक्रमms the करोमुख्य validation on the given device in the
 *	current execution thपढ़ो.  Since DV operations may sleep,
 *	the current thपढ़ो must have user context.  Also no SCSI
 *	related locks that would deadlock I/O issued by the DV may
 *	be held.
 */
व्योम
spi_dv_device(काष्ठा scsi_device *sdev)
अणु
	काष्ठा scsi_target *starget = sdev->sdev_target;
	u8 *buffer;
	स्थिर पूर्णांक len = SPI_MAX_ECHO_BUFFER_SIZE*2;

	/*
	 * Because this function and the घातer management code both call
	 * scsi_device_quiesce(), it is not safe to perक्रमm करोमुख्य validation
	 * जबतक suspend or resume is in progress. Hence the
	 * lock/unlock_प्रणाली_sleep() calls.
	 */
	lock_प्रणाली_sleep();

	अगर (scsi_स्वतःpm_get_device(sdev))
		जाओ unlock_प्रणाली_sleep;

	अगर (unlikely(spi_dv_in_progress(starget)))
		जाओ put_स्वतःpm;

	अगर (unlikely(scsi_device_get(sdev)))
		जाओ put_स्वतःpm;

	spi_dv_in_progress(starget) = 1;

	buffer = kzalloc(len, GFP_KERNEL);

	अगर (unlikely(!buffer))
		जाओ put_sdev;

	/* We need to verअगरy that the actual device will quiesce; the
	 * later target quiesce is just a nice to have */
	अगर (unlikely(scsi_device_quiesce(sdev)))
		जाओ मुक्त_buffer;

	scsi_target_quiesce(starget);

	spi_dv_pending(starget) = 1;
	mutex_lock(&spi_dv_mutex(starget));

	starget_prपूर्णांकk(KERN_INFO, starget, "Beginning Domain Validation\n");

	spi_dv_device_पूर्णांकernal(sdev, buffer);

	starget_prपूर्णांकk(KERN_INFO, starget, "Ending Domain Validation\n");

	mutex_unlock(&spi_dv_mutex(starget));
	spi_dv_pending(starget) = 0;

	scsi_target_resume(starget);

	spi_initial_dv(starget) = 1;

मुक्त_buffer:
	kमुक्त(buffer);

put_sdev:
	spi_dv_in_progress(starget) = 0;
	scsi_device_put(sdev);
put_स्वतःpm:
	scsi_स्वतःpm_put_device(sdev);

unlock_प्रणाली_sleep:
	unlock_प्रणाली_sleep();
पूर्ण
EXPORT_SYMBOL(spi_dv_device);

काष्ठा work_queue_wrapper अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा scsi_device	*sdev;
पूर्ण;

अटल व्योम
spi_dv_device_work_wrapper(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा work_queue_wrapper *wqw =
		container_of(work, काष्ठा work_queue_wrapper, work);
	काष्ठा scsi_device *sdev = wqw->sdev;

	kमुक्त(wqw);
	spi_dv_device(sdev);
	spi_dv_pending(sdev->sdev_target) = 0;
	scsi_device_put(sdev);
पूर्ण


/**
 *	spi_schedule_dv_device - schedule करोमुख्य validation to occur on the device
 *	@sdev:	The device to validate
 *
 *	Identical to spi_dv_device() above, except that the DV will be
 *	scheduled to occur in a workqueue later.  All memory allocations
 *	are atomic, so may be called from any context including those holding
 *	SCSI locks.
 */
व्योम
spi_schedule_dv_device(काष्ठा scsi_device *sdev)
अणु
	काष्ठा work_queue_wrapper *wqw =
		kदो_स्मृति(माप(काष्ठा work_queue_wrapper), GFP_ATOMIC);

	अगर (unlikely(!wqw))
		वापस;

	अगर (unlikely(spi_dv_pending(sdev->sdev_target))) अणु
		kमुक्त(wqw);
		वापस;
	पूर्ण
	/* Set pending early (dv_device करोesn't check it, only sets it) */
	spi_dv_pending(sdev->sdev_target) = 1;
	अगर (unlikely(scsi_device_get(sdev))) अणु
		kमुक्त(wqw);
		spi_dv_pending(sdev->sdev_target) = 0;
		वापस;
	पूर्ण

	INIT_WORK(&wqw->work, spi_dv_device_work_wrapper);
	wqw->sdev = sdev;

	schedule_work(&wqw->work);
पूर्ण
EXPORT_SYMBOL(spi_schedule_dv_device);

/**
 * spi_display_xfer_agreement - Prपूर्णांक the current target transfer agreement
 * @starget: The target क्रम which to display the agreement
 *
 * Each SPI port is required to मुख्यtain a transfer agreement क्रम each
 * other port on the bus.  This function prपूर्णांकs a one-line summary of
 * the current agreement; more detailed inक्रमmation is available in sysfs.
 */
व्योम spi_display_xfer_agreement(काष्ठा scsi_target *starget)
अणु
	काष्ठा spi_transport_attrs *tp;
	tp = (काष्ठा spi_transport_attrs *)&starget->starget_data;

	अगर (tp->offset > 0 && tp->period > 0) अणु
		अचिन्हित पूर्णांक picosec, kb100;
		अक्षर *scsi = "FAST-?";
		अक्षर पंचांगp[8];

		अगर (tp->period <= SPI_STATIC_PPR) अणु
			picosec = ppr_to_ps[tp->period];
			चयन (tp->period) अणु
				हाल  7: scsi = "FAST-320"; अवरोध;
				हाल  8: scsi = "FAST-160"; अवरोध;
				हाल  9: scsi = "FAST-80"; अवरोध;
				हाल 10:
				हाल 11: scsi = "FAST-40"; अवरोध;
				हाल 12: scsi = "FAST-20"; अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			picosec = tp->period * 4000;
			अगर (tp->period < 25)
				scsi = "FAST-20";
			अन्यथा अगर (tp->period < 50)
				scsi = "FAST-10";
			अन्यथा
				scsi = "FAST-5";
		पूर्ण

		kb100 = (10000000 + picosec / 2) / picosec;
		अगर (tp->width)
			kb100 *= 2;
		sprपूर्णांक_frac(पंचांगp, picosec, 1000);

		dev_info(&starget->dev,
			 "%s %sSCSI %d.%d MB/s %s%s%s%s%s%s%s%s (%s ns, offset %d)\n",
			 scsi, tp->width ? "WIDE " : "", kb100/10, kb100 % 10,
			 tp->dt ? "DT" : "ST",
			 tp->iu ? " IU" : "",
			 tp->qas  ? " QAS" : "",
			 tp->rd_strm ? " RDSTRM" : "",
			 tp->rti ? " RTI" : "",
			 tp->wr_flow ? " WRFLOW" : "",
			 tp->pcomp_en ? " PCOMP" : "",
			 tp->hold_mcs ? " HMCS" : "",
			 पंचांगp, tp->offset);
	पूर्ण अन्यथा अणु
		dev_info(&starget->dev, "%sasynchronous\n",
				tp->width ? "wide " : "");
	पूर्ण
पूर्ण
EXPORT_SYMBOL(spi_display_xfer_agreement);

पूर्णांक spi_populate_width_msg(अचिन्हित अक्षर *msg, पूर्णांक width)
अणु
	msg[0] = EXTENDED_MESSAGE;
	msg[1] = 2;
	msg[2] = EXTENDED_WDTR;
	msg[3] = width;
	वापस 4;
पूर्ण
EXPORT_SYMBOL_GPL(spi_populate_width_msg);

पूर्णांक spi_populate_sync_msg(अचिन्हित अक्षर *msg, पूर्णांक period, पूर्णांक offset)
अणु
	msg[0] = EXTENDED_MESSAGE;
	msg[1] = 3;
	msg[2] = EXTENDED_SDTR;
	msg[3] = period;
	msg[4] = offset;
	वापस 5;
पूर्ण
EXPORT_SYMBOL_GPL(spi_populate_sync_msg);

पूर्णांक spi_populate_ppr_msg(अचिन्हित अक्षर *msg, पूर्णांक period, पूर्णांक offset,
		पूर्णांक width, पूर्णांक options)
अणु
	msg[0] = EXTENDED_MESSAGE;
	msg[1] = 6;
	msg[2] = EXTENDED_PPR;
	msg[3] = period;
	msg[4] = 0;
	msg[5] = offset;
	msg[6] = width;
	msg[7] = options;
	वापस 8;
पूर्ण
EXPORT_SYMBOL_GPL(spi_populate_ppr_msg);

/**
 * spi_populate_tag_msg - place a tag message in a buffer
 * @msg:	poपूर्णांकer to the area to place the tag
 * @cmd:	poपूर्णांकer to the scsi command क्रम the tag
 *
 * Notes:
 *	deचिन्हित to create the correct type of tag message क्रम the 
 *	particular request.  Returns the size of the tag message.
 *	May वापस 0 अगर TCQ is disabled क्रम this device.
 **/
पूर्णांक spi_populate_tag_msg(अचिन्हित अक्षर *msg, काष्ठा scsi_cmnd *cmd)
अणु
        अगर (cmd->flags & SCMD_TAGGED) अणु
		*msg++ = SIMPLE_QUEUE_TAG;
        	*msg++ = cmd->request->tag;
        	वापस 2;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spi_populate_tag_msg);

#अगर_घोषित CONFIG_SCSI_CONSTANTS
अटल स्थिर अक्षर * स्थिर one_byte_msgs[] = अणु
/* 0x00 */ "Task Complete", शून्य /* Extended Message */, "Save Pointers",
/* 0x03 */ "Restore Pointers", "Disconnect", "Initiator Error", 
/* 0x06 */ "Abort Task Set", "Message Reject", "Nop", "Message Parity Error",
/* 0x0a */ "Linked Command Complete", "Linked Command Complete w/flag",
/* 0x0c */ "Target Reset", "Abort Task", "Clear Task Set", 
/* 0x0f */ "Initiate Recovery", "Release Recovery",
/* 0x11 */ "Terminate Process", "Continue Task", "Target Transfer Disable",
/* 0x14 */ शून्य, शून्य, "Clear ACA", "LUN Reset"
पूर्ण;

अटल स्थिर अक्षर * स्थिर two_byte_msgs[] = अणु
/* 0x20 */ "Simple Queue Tag", "Head of Queue Tag", "Ordered Queue Tag",
/* 0x23 */ "Ignore Wide Residue", "ACA"
पूर्ण;

अटल स्थिर अक्षर * स्थिर extended_msgs[] = अणु
/* 0x00 */ "Modify Data Pointer", "Synchronous Data Transfer Request",
/* 0x02 */ "SCSI-I Extended Identify", "Wide Data Transfer Request",
/* 0x04 */ "Parallel Protocol Request", "Modify Bidirectional Data Pointer"
पूर्ण;

अटल व्योम prपूर्णांक_nego(स्थिर अचिन्हित अक्षर *msg, पूर्णांक per, पूर्णांक off, पूर्णांक width)
अणु
	अगर (per) अणु
		अक्षर buf[20];
		period_to_str(buf, msg[per]);
		prपूर्णांकk("period = %s ns ", buf);
	पूर्ण

	अगर (off)
		prपूर्णांकk("offset = %d ", msg[off]);
	अगर (width)
		prपूर्णांकk("width = %d ", 8 << msg[width]);
पूर्ण

अटल व्योम prपूर्णांक_ptr(स्थिर अचिन्हित अक्षर *msg, पूर्णांक msb, स्थिर अक्षर *desc)
अणु
	पूर्णांक ptr = (msg[msb] << 24) | (msg[msb+1] << 16) | (msg[msb+2] << 8) |
			msg[msb+3];
	prपूर्णांकk("%s = %d ", desc, ptr);
पूर्ण

पूर्णांक spi_prपूर्णांक_msg(स्थिर अचिन्हित अक्षर *msg)
अणु
	पूर्णांक len = 1, i;
	अगर (msg[0] == EXTENDED_MESSAGE) अणु
		len = 2 + msg[1];
		अगर (len == 2)
			len += 256;
		अगर (msg[2] < ARRAY_SIZE(extended_msgs))
			prपूर्णांकk ("%s ", extended_msgs[msg[2]]); 
		अन्यथा 
			prपूर्णांकk ("Extended Message, reserved code (0x%02x) ",
				(पूर्णांक) msg[2]);
		चयन (msg[2]) अणु
		हाल EXTENDED_MODIFY_DATA_POINTER:
			prपूर्णांक_ptr(msg, 3, "pointer");
			अवरोध;
		हाल EXTENDED_SDTR:
			prपूर्णांक_nego(msg, 3, 4, 0);
			अवरोध;
		हाल EXTENDED_WDTR:
			prपूर्णांक_nego(msg, 0, 0, 3);
			अवरोध;
		हाल EXTENDED_PPR:
			prपूर्णांक_nego(msg, 3, 5, 6);
			अवरोध;
		हाल EXTENDED_MODIFY_BIDI_DATA_PTR:
			prपूर्णांक_ptr(msg, 3, "out");
			prपूर्णांक_ptr(msg, 7, "in");
			अवरोध;
		शेष:
		क्रम (i = 2; i < len; ++i) 
			prपूर्णांकk("%02x ", msg[i]);
		पूर्ण
	/* Identअगरy */
	पूर्ण अन्यथा अगर (msg[0] & 0x80) अणु
		prपूर्णांकk("Identify disconnect %sallowed %s %d ",
			(msg[0] & 0x40) ? "" : "not ",
			(msg[0] & 0x20) ? "target routine" : "lun",
			msg[0] & 0x7);
	/* Normal One byte */
	पूर्ण अन्यथा अगर (msg[0] < 0x1f) अणु
		अगर (msg[0] < ARRAY_SIZE(one_byte_msgs) && one_byte_msgs[msg[0]])
			prपूर्णांकk("%s ", one_byte_msgs[msg[0]]);
		अन्यथा
			prपूर्णांकk("reserved (%02x) ", msg[0]);
	पूर्ण अन्यथा अगर (msg[0] == 0x55) अणु
		prपूर्णांकk("QAS Request ");
	/* Two byte */
	पूर्ण अन्यथा अगर (msg[0] <= 0x2f) अणु
		अगर ((msg[0] - 0x20) < ARRAY_SIZE(two_byte_msgs))
			prपूर्णांकk("%s %02x ", two_byte_msgs[msg[0] - 0x20], 
				msg[1]);
		अन्यथा 
			prपूर्णांकk("reserved two byte (%02x %02x) ", 
				msg[0], msg[1]);
		len = 2;
	पूर्ण अन्यथा 
		prपूर्णांकk("reserved ");
	वापस len;
पूर्ण
EXPORT_SYMBOL(spi_prपूर्णांक_msg);

#अन्यथा  /* अगरndef CONFIG_SCSI_CONSTANTS */

पूर्णांक spi_prपूर्णांक_msg(स्थिर अचिन्हित अक्षर *msg)
अणु
	पूर्णांक len = 1, i;

	अगर (msg[0] == EXTENDED_MESSAGE) अणु
		len = 2 + msg[1];
		अगर (len == 2)
			len += 256;
		क्रम (i = 0; i < len; ++i)
			prपूर्णांकk("%02x ", msg[i]);
	/* Identअगरy */
	पूर्ण अन्यथा अगर (msg[0] & 0x80) अणु
		prपूर्णांकk("%02x ", msg[0]);
	/* Normal One byte */
	पूर्ण अन्यथा अगर ((msg[0] < 0x1f) || (msg[0] == 0x55)) अणु
		prपूर्णांकk("%02x ", msg[0]);
	/* Two byte */
	पूर्ण अन्यथा अगर (msg[0] <= 0x2f) अणु
		prपूर्णांकk("%02x %02x", msg[0], msg[1]);
		len = 2;
	पूर्ण अन्यथा 
		prपूर्णांकk("%02x ", msg[0]);
	वापस len;
पूर्ण
EXPORT_SYMBOL(spi_prपूर्णांक_msg);
#पूर्ण_अगर /* ! CONFIG_SCSI_CONSTANTS */

अटल पूर्णांक spi_device_match(काष्ठा attribute_container *cont,
			    काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev;
	काष्ठा Scsi_Host *shost;
	काष्ठा spi_पूर्णांकernal *i;

	अगर (!scsi_is_sdev_device(dev))
		वापस 0;

	sdev = to_scsi_device(dev);
	shost = sdev->host;
	अगर (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &spi_host_class.class)
		वापस 0;
	/* Note: this class has no device attributes, so it has
	 * no per-HBA allocation and thus we करोn't need to distinguish
	 * the attribute containers क्रम the device */
	i = to_spi_पूर्णांकernal(shost->transportt);
	अगर (i->f->deny_binding && i->f->deny_binding(sdev->sdev_target))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक spi_target_match(काष्ठा attribute_container *cont,
			    काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा scsi_target *starget;
	काष्ठा spi_पूर्णांकernal *i;

	अगर (!scsi_is_target_device(dev))
		वापस 0;

	shost = dev_to_shost(dev->parent);
	अगर (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &spi_host_class.class)
		वापस 0;

	i = to_spi_पूर्णांकernal(shost->transportt);
	starget = to_scsi_target(dev);

	अगर (i->f->deny_binding && i->f->deny_binding(starget))
		वापस 0;

	वापस &i->t.target_attrs.ac == cont;
पूर्ण

अटल DECLARE_TRANSPORT_CLASS(spi_transport_class,
			       "spi_transport",
			       spi_setup_transport_attrs,
			       शून्य,
			       spi_target_configure);

अटल DECLARE_ANON_TRANSPORT_CLASS(spi_device_class,
				    spi_device_match,
				    spi_device_configure);

अटल काष्ठा attribute *host_attributes[] = अणु
	&dev_attr_संकेतling.attr,
	&dev_attr_host_width.attr,
	&dev_attr_hba_id.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group host_attribute_group = अणु
	.attrs = host_attributes,
पूर्ण;

अटल पूर्णांक spi_host_configure(काष्ठा transport_container *tc,
			      काष्ठा device *dev,
			      काष्ठा device *cdev)
अणु
	काष्ठा kobject *kobj = &cdev->kobj;
	काष्ठा Scsi_Host *shost = transport_class_to_shost(cdev);
	काष्ठा spi_पूर्णांकernal *si = to_spi_पूर्णांकernal(shost->transportt);
	काष्ठा attribute *attr = &dev_attr_संकेतling.attr;
	पूर्णांक rc = 0;

	अगर (si->f->set_संकेतling)
		rc = sysfs_chmod_file(kobj, attr, attr->mode | S_IWUSR);

	वापस rc;
पूर्ण

/* वापसs true अगर we should be showing the variable.  Also
 * overloads the वापस by setting 1<<1 अगर the attribute should
 * be ग_लिखोable */
#घोषणा TARGET_ATTRIBUTE_HELPER(name) \
	(si->f->show_##name ? S_IRUGO : 0) | \
	(si->f->set_##name ? S_IWUSR : 0)

अटल umode_t target_attribute_is_visible(काष्ठा kobject *kobj,
					  काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा device *cdev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा scsi_target *starget = transport_class_to_starget(cdev);
	काष्ठा Scsi_Host *shost = transport_class_to_shost(cdev);
	काष्ठा spi_पूर्णांकernal *si = to_spi_पूर्णांकernal(shost->transportt);

	अगर (attr == &dev_attr_period.attr &&
	    spi_support_sync(starget))
		वापस TARGET_ATTRIBUTE_HELPER(period);
	अन्यथा अगर (attr == &dev_attr_min_period.attr &&
		 spi_support_sync(starget))
		वापस TARGET_ATTRIBUTE_HELPER(period);
	अन्यथा अगर (attr == &dev_attr_offset.attr &&
		 spi_support_sync(starget))
		वापस TARGET_ATTRIBUTE_HELPER(offset);
	अन्यथा अगर (attr == &dev_attr_max_offset.attr &&
		 spi_support_sync(starget))
		वापस TARGET_ATTRIBUTE_HELPER(offset);
	अन्यथा अगर (attr == &dev_attr_width.attr &&
		 spi_support_wide(starget))
		वापस TARGET_ATTRIBUTE_HELPER(width);
	अन्यथा अगर (attr == &dev_attr_max_width.attr &&
		 spi_support_wide(starget))
		वापस TARGET_ATTRIBUTE_HELPER(width);
	अन्यथा अगर (attr == &dev_attr_iu.attr &&
		 spi_support_ius(starget))
		वापस TARGET_ATTRIBUTE_HELPER(iu);
	अन्यथा अगर (attr == &dev_attr_max_iu.attr &&
		 spi_support_ius(starget))
		वापस TARGET_ATTRIBUTE_HELPER(iu);
	अन्यथा अगर (attr == &dev_attr_dt.attr &&
		 spi_support_dt(starget))
		वापस TARGET_ATTRIBUTE_HELPER(dt);
	अन्यथा अगर (attr == &dev_attr_qas.attr &&
		 spi_support_qas(starget))
		वापस TARGET_ATTRIBUTE_HELPER(qas);
	अन्यथा अगर (attr == &dev_attr_max_qas.attr &&
		 spi_support_qas(starget))
		वापस TARGET_ATTRIBUTE_HELPER(qas);
	अन्यथा अगर (attr == &dev_attr_wr_flow.attr &&
		 spi_support_ius(starget))
		वापस TARGET_ATTRIBUTE_HELPER(wr_flow);
	अन्यथा अगर (attr == &dev_attr_rd_strm.attr &&
		 spi_support_ius(starget))
		वापस TARGET_ATTRIBUTE_HELPER(rd_strm);
	अन्यथा अगर (attr == &dev_attr_rti.attr &&
		 spi_support_ius(starget))
		वापस TARGET_ATTRIBUTE_HELPER(rti);
	अन्यथा अगर (attr == &dev_attr_pcomp_en.attr &&
		 spi_support_ius(starget))
		वापस TARGET_ATTRIBUTE_HELPER(pcomp_en);
	अन्यथा अगर (attr == &dev_attr_hold_mcs.attr &&
		 spi_support_ius(starget))
		वापस TARGET_ATTRIBUTE_HELPER(hold_mcs);
	अन्यथा अगर (attr == &dev_attr_revalidate.attr)
		वापस S_IWUSR;

	वापस 0;
पूर्ण

अटल काष्ठा attribute *target_attributes[] = अणु
	&dev_attr_period.attr,
	&dev_attr_min_period.attr,
	&dev_attr_offset.attr,
	&dev_attr_max_offset.attr,
	&dev_attr_width.attr,
	&dev_attr_max_width.attr,
	&dev_attr_iu.attr,
	&dev_attr_max_iu.attr,
	&dev_attr_dt.attr,
	&dev_attr_qas.attr,
	&dev_attr_max_qas.attr,
	&dev_attr_wr_flow.attr,
	&dev_attr_rd_strm.attr,
	&dev_attr_rti.attr,
	&dev_attr_pcomp_en.attr,
	&dev_attr_hold_mcs.attr,
	&dev_attr_revalidate.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group target_attribute_group = अणु
	.attrs = target_attributes,
	.is_visible = target_attribute_is_visible,
पूर्ण;

अटल पूर्णांक spi_target_configure(काष्ठा transport_container *tc,
				काष्ठा device *dev,
				काष्ठा device *cdev)
अणु
	काष्ठा kobject *kobj = &cdev->kobj;

	/* क्रमce an update based on parameters पढ़ो from the device */
	sysfs_update_group(kobj, &target_attribute_group);

	वापस 0;
पूर्ण

काष्ठा scsi_transport_ढाँचा *
spi_attach_transport(काष्ठा spi_function_ढाँचा *ft)
अणु
	काष्ठा spi_पूर्णांकernal *i = kzalloc(माप(काष्ठा spi_पूर्णांकernal),
					 GFP_KERNEL);

	अगर (unlikely(!i))
		वापस शून्य;

	i->t.target_attrs.ac.class = &spi_transport_class.class;
	i->t.target_attrs.ac.grp = &target_attribute_group;
	i->t.target_attrs.ac.match = spi_target_match;
	transport_container_रेजिस्टर(&i->t.target_attrs);
	i->t.target_size = माप(काष्ठा spi_transport_attrs);
	i->t.host_attrs.ac.class = &spi_host_class.class;
	i->t.host_attrs.ac.grp = &host_attribute_group;
	i->t.host_attrs.ac.match = spi_host_match;
	transport_container_रेजिस्टर(&i->t.host_attrs);
	i->t.host_size = माप(काष्ठा spi_host_attrs);
	i->f = ft;

	वापस &i->t;
पूर्ण
EXPORT_SYMBOL(spi_attach_transport);

व्योम spi_release_transport(काष्ठा scsi_transport_ढाँचा *t)
अणु
	काष्ठा spi_पूर्णांकernal *i = to_spi_पूर्णांकernal(t);

	transport_container_unरेजिस्टर(&i->t.target_attrs);
	transport_container_unरेजिस्टर(&i->t.host_attrs);

	kमुक्त(i);
पूर्ण
EXPORT_SYMBOL(spi_release_transport);

अटल __init पूर्णांक spi_transport_init(व्योम)
अणु
	पूर्णांक error = scsi_dev_info_add_list(SCSI_DEVINFO_SPI,
					   "SCSI Parallel Transport Class");
	अगर (!error) अणु
		पूर्णांक i;

		क्रम (i = 0; spi_अटल_device_list[i].venकरोr; i++)
			scsi_dev_info_list_add_keyed(1,	/* compatible */
						     spi_अटल_device_list[i].venकरोr,
						     spi_अटल_device_list[i].model,
						     शून्य,
						     spi_अटल_device_list[i].flags,
						     SCSI_DEVINFO_SPI);
	पूर्ण

	error = transport_class_रेजिस्टर(&spi_transport_class);
	अगर (error)
		वापस error;
	error = anon_transport_class_रेजिस्टर(&spi_device_class);
	वापस transport_class_रेजिस्टर(&spi_host_class);
पूर्ण

अटल व्योम __निकास spi_transport_निकास(व्योम)
अणु
	transport_class_unरेजिस्टर(&spi_transport_class);
	anon_transport_class_unरेजिस्टर(&spi_device_class);
	transport_class_unरेजिस्टर(&spi_host_class);
	scsi_dev_info_हटाओ_list(SCSI_DEVINFO_SPI);
पूर्ण

MODULE_AUTHOR("Martin Hicks");
MODULE_DESCRIPTION("SPI Transport Attributes");
MODULE_LICENSE("GPL");

module_init(spi_transport_init);
module_निकास(spi_transport_निकास);
