<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Channel path related status regions क्रम vfio_ccw
 *
 * Copyright IBM Corp. 2020
 *
 * Author(s): Farhan Ali <alअगरm@linux.ibm.com>
 *            Eric Farman <farman@linux.ibm.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/vfपन.स>
#समावेश "vfio_ccw_private.h"

अटल sमाप_प्रकार vfio_ccw_schib_region_पढ़ो(काष्ठा vfio_ccw_निजी *निजी,
					  अक्षर __user *buf, माप_प्रकार count,
					  loff_t *ppos)
अणु
	अचिन्हित पूर्णांक i = VFIO_CCW_OFFSET_TO_INDEX(*ppos) - VFIO_CCW_NUM_REGIONS;
	loff_t pos = *ppos & VFIO_CCW_OFFSET_MASK;
	काष्ठा ccw_schib_region *region;
	पूर्णांक ret;

	अगर (pos + count > माप(*region))
		वापस -EINVAL;

	mutex_lock(&निजी->io_mutex);
	region = निजी->region[i].data;

	अगर (cio_update_schib(निजी->sch)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	स_नकल(region, &निजी->sch->schib, माप(*region));

	अगर (copy_to_user(buf, (व्योम *)region + pos, count)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	ret = count;

out:
	mutex_unlock(&निजी->io_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार vfio_ccw_schib_region_ग_लिखो(काष्ठा vfio_ccw_निजी *निजी,
					   स्थिर अक्षर __user *buf, माप_प्रकार count,
					   loff_t *ppos)
अणु
	वापस -EINVAL;
पूर्ण


अटल व्योम vfio_ccw_schib_region_release(काष्ठा vfio_ccw_निजी *निजी,
					  काष्ठा vfio_ccw_region *region)
अणु

पूर्ण

अटल स्थिर काष्ठा vfio_ccw_regops vfio_ccw_schib_region_ops = अणु
	.पढ़ो = vfio_ccw_schib_region_पढ़ो,
	.ग_लिखो = vfio_ccw_schib_region_ग_लिखो,
	.release = vfio_ccw_schib_region_release,
पूर्ण;

पूर्णांक vfio_ccw_रेजिस्टर_schib_dev_regions(काष्ठा vfio_ccw_निजी *निजी)
अणु
	वापस vfio_ccw_रेजिस्टर_dev_region(निजी,
					    VFIO_REGION_SUBTYPE_CCW_SCHIB,
					    &vfio_ccw_schib_region_ops,
					    माप(काष्ठा ccw_schib_region),
					    VFIO_REGION_INFO_FLAG_READ,
					    निजी->schib_region);
पूर्ण

अटल sमाप_प्रकार vfio_ccw_crw_region_पढ़ो(काष्ठा vfio_ccw_निजी *निजी,
					अक्षर __user *buf, माप_प्रकार count,
					loff_t *ppos)
अणु
	अचिन्हित पूर्णांक i = VFIO_CCW_OFFSET_TO_INDEX(*ppos) - VFIO_CCW_NUM_REGIONS;
	loff_t pos = *ppos & VFIO_CCW_OFFSET_MASK;
	काष्ठा ccw_crw_region *region;
	काष्ठा vfio_ccw_crw *crw;
	पूर्णांक ret;

	अगर (pos + count > माप(*region))
		वापस -EINVAL;

	crw = list_first_entry_or_null(&निजी->crw,
				       काष्ठा vfio_ccw_crw, next);

	अगर (crw)
		list_del(&crw->next);

	mutex_lock(&निजी->io_mutex);
	region = निजी->region[i].data;

	अगर (crw)
		स_नकल(&region->crw, &crw->crw, माप(region->crw));

	अगर (copy_to_user(buf, (व्योम *)region + pos, count))
		ret = -EFAULT;
	अन्यथा
		ret = count;

	region->crw = 0;

	mutex_unlock(&निजी->io_mutex);

	kमुक्त(crw);

	/* Notअगरy the guest अगर more CRWs are on our queue */
	अगर (!list_empty(&निजी->crw) && निजी->crw_trigger)
		eventfd_संकेत(निजी->crw_trigger, 1);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार vfio_ccw_crw_region_ग_लिखो(काष्ठा vfio_ccw_निजी *निजी,
					 स्थिर अक्षर __user *buf, माप_प्रकार count,
					 loff_t *ppos)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम vfio_ccw_crw_region_release(काष्ठा vfio_ccw_निजी *निजी,
					काष्ठा vfio_ccw_region *region)
अणु

पूर्ण

अटल स्थिर काष्ठा vfio_ccw_regops vfio_ccw_crw_region_ops = अणु
	.पढ़ो = vfio_ccw_crw_region_पढ़ो,
	.ग_लिखो = vfio_ccw_crw_region_ग_लिखो,
	.release = vfio_ccw_crw_region_release,
पूर्ण;

पूर्णांक vfio_ccw_रेजिस्टर_crw_dev_regions(काष्ठा vfio_ccw_निजी *निजी)
अणु
	वापस vfio_ccw_रेजिस्टर_dev_region(निजी,
					    VFIO_REGION_SUBTYPE_CCW_CRW,
					    &vfio_ccw_crw_region_ops,
					    माप(काष्ठा ccw_crw_region),
					    VFIO_REGION_INFO_FLAG_READ,
					    निजी->crw_region);
पूर्ण
