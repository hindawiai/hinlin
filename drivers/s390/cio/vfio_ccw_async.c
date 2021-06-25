<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Async I/O region क्रम vfio_ccw
 *
 * Copyright Red Hat, Inc. 2019
 *
 * Author(s): Cornelia Huck <cohuck@redhat.com>
 */

#समावेश <linux/vfपन.स>
#समावेश <linux/mdev.h>

#समावेश "vfio_ccw_private.h"

अटल sमाप_प्रकार vfio_ccw_async_region_पढ़ो(काष्ठा vfio_ccw_निजी *निजी,
					  अक्षर __user *buf, माप_प्रकार count,
					  loff_t *ppos)
अणु
	अचिन्हित पूर्णांक i = VFIO_CCW_OFFSET_TO_INDEX(*ppos) - VFIO_CCW_NUM_REGIONS;
	loff_t pos = *ppos & VFIO_CCW_OFFSET_MASK;
	काष्ठा ccw_cmd_region *region;
	पूर्णांक ret;

	अगर (pos + count > माप(*region))
		वापस -EINVAL;

	mutex_lock(&निजी->io_mutex);
	region = निजी->region[i].data;
	अगर (copy_to_user(buf, (व्योम *)region + pos, count))
		ret = -EFAULT;
	अन्यथा
		ret = count;
	mutex_unlock(&निजी->io_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार vfio_ccw_async_region_ग_लिखो(काष्ठा vfio_ccw_निजी *निजी,
					   स्थिर अक्षर __user *buf, माप_प्रकार count,
					   loff_t *ppos)
अणु
	अचिन्हित पूर्णांक i = VFIO_CCW_OFFSET_TO_INDEX(*ppos) - VFIO_CCW_NUM_REGIONS;
	loff_t pos = *ppos & VFIO_CCW_OFFSET_MASK;
	काष्ठा ccw_cmd_region *region;
	पूर्णांक ret;

	अगर (pos + count > माप(*region))
		वापस -EINVAL;

	अगर (!mutex_trylock(&निजी->io_mutex))
		वापस -EAGAIN;

	region = निजी->region[i].data;
	अगर (copy_from_user((व्योम *)region + pos, buf, count)) अणु
		ret = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	vfio_ccw_fsm_event(निजी, VFIO_CCW_EVENT_ASYNC_REQ);

	ret = region->ret_code ? region->ret_code : count;

out_unlock:
	mutex_unlock(&निजी->io_mutex);
	वापस ret;
पूर्ण

अटल व्योम vfio_ccw_async_region_release(काष्ठा vfio_ccw_निजी *निजी,
					  काष्ठा vfio_ccw_region *region)
अणु

पूर्ण

अटल स्थिर काष्ठा vfio_ccw_regops vfio_ccw_async_region_ops = अणु
	.पढ़ो = vfio_ccw_async_region_पढ़ो,
	.ग_लिखो = vfio_ccw_async_region_ग_लिखो,
	.release = vfio_ccw_async_region_release,
पूर्ण;

पूर्णांक vfio_ccw_रेजिस्टर_async_dev_regions(काष्ठा vfio_ccw_निजी *निजी)
अणु
	वापस vfio_ccw_रेजिस्टर_dev_region(निजी,
					    VFIO_REGION_SUBTYPE_CCW_ASYNC_CMD,
					    &vfio_ccw_async_region_ops,
					    माप(काष्ठा ccw_cmd_region),
					    VFIO_REGION_INFO_FLAG_READ |
					    VFIO_REGION_INFO_FLAG_WRITE,
					    निजी->cmd_region);
पूर्ण
