<शैली गुरु>
/*
 * Copyright तऊ 2015 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Rafael Antognolli <rafael.antognolli@पूर्णांकel.com>
 *
 */

#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/uपन.स>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_dp_mst_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_crtc_helper_internal.h"

काष्ठा drm_dp_aux_dev अणु
	अचिन्हित index;
	काष्ठा drm_dp_aux *aux;
	काष्ठा device *dev;
	काष्ठा kref refcount;
	atomic_t usecount;
पूर्ण;

#घोषणा DRM_AUX_MINORS	256
#घोषणा AUX_MAX_OFFSET	(1 << 20)
अटल DEFINE_IDR(aux_idr);
अटल DEFINE_MUTEX(aux_idr_mutex);
अटल काष्ठा class *drm_dp_aux_dev_class;
अटल पूर्णांक drm_dev_major = -1;

अटल काष्ठा drm_dp_aux_dev *drm_dp_aux_dev_get_by_minor(अचिन्हित index)
अणु
	काष्ठा drm_dp_aux_dev *aux_dev = शून्य;

	mutex_lock(&aux_idr_mutex);
	aux_dev = idr_find(&aux_idr, index);
	अगर (aux_dev && !kref_get_unless_zero(&aux_dev->refcount))
		aux_dev = शून्य;
	mutex_unlock(&aux_idr_mutex);

	वापस aux_dev;
पूर्ण

अटल काष्ठा drm_dp_aux_dev *alloc_drm_dp_aux_dev(काष्ठा drm_dp_aux *aux)
अणु
	काष्ठा drm_dp_aux_dev *aux_dev;
	पूर्णांक index;

	aux_dev = kzalloc(माप(*aux_dev), GFP_KERNEL);
	अगर (!aux_dev)
		वापस ERR_PTR(-ENOMEM);
	aux_dev->aux = aux;
	atomic_set(&aux_dev->usecount, 1);
	kref_init(&aux_dev->refcount);

	mutex_lock(&aux_idr_mutex);
	index = idr_alloc(&aux_idr, aux_dev, 0, DRM_AUX_MINORS, GFP_KERNEL);
	mutex_unlock(&aux_idr_mutex);
	अगर (index < 0) अणु
		kमुक्त(aux_dev);
		वापस ERR_PTR(index);
	पूर्ण
	aux_dev->index = index;

	वापस aux_dev;
पूर्ण

अटल व्योम release_drm_dp_aux_dev(काष्ठा kref *ref)
अणु
	काष्ठा drm_dp_aux_dev *aux_dev =
		container_of(ref, काष्ठा drm_dp_aux_dev, refcount);

	kमुक्त(aux_dev);
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार res;
	काष्ठा drm_dp_aux_dev *aux_dev =
		drm_dp_aux_dev_get_by_minor(MINOR(dev->devt));

	अगर (!aux_dev)
		वापस -ENODEV;

	res = प्र_लिखो(buf, "%s\n", aux_dev->aux->name);
	kref_put(&aux_dev->refcount, release_drm_dp_aux_dev);

	वापस res;
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *drm_dp_aux_attrs[] = अणु
	&dev_attr_name.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(drm_dp_aux);

अटल पूर्णांक auxdev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor = iminor(inode);
	काष्ठा drm_dp_aux_dev *aux_dev;

	aux_dev = drm_dp_aux_dev_get_by_minor(minor);
	अगर (!aux_dev)
		वापस -ENODEV;

	file->निजी_data = aux_dev;
	वापस 0;
पूर्ण

अटल loff_t auxdev_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	वापस fixed_size_llseek(file, offset, whence, AUX_MAX_OFFSET);
पूर्ण

अटल sमाप_प्रकार auxdev_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा drm_dp_aux_dev *aux_dev = iocb->ki_filp->निजी_data;
	loff_t pos = iocb->ki_pos;
	sमाप_प्रकार res = 0;

	अगर (!atomic_inc_not_zero(&aux_dev->usecount))
		वापस -ENODEV;

	iov_iter_truncate(to, AUX_MAX_OFFSET - pos);

	जबतक (iov_iter_count(to)) अणु
		uपूर्णांक8_t buf[DP_AUX_MAX_PAYLOAD_BYTES];
		sमाप_प्रकार toकरो = min(iov_iter_count(to), माप(buf));

		अगर (संकेत_pending(current)) अणु
			res = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		res = drm_dp_dpcd_पढ़ो(aux_dev->aux, pos, buf, toकरो);

		अगर (res <= 0)
			अवरोध;

		अगर (copy_to_iter(buf, res, to) != res) अणु
			res = -EFAULT;
			अवरोध;
		पूर्ण

		pos += res;
	पूर्ण

	अगर (pos != iocb->ki_pos)
		res = pos - iocb->ki_pos;
	iocb->ki_pos = pos;

	अगर (atomic_dec_and_test(&aux_dev->usecount))
		wake_up_var(&aux_dev->usecount);

	वापस res;
पूर्ण

अटल sमाप_प्रकार auxdev_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा drm_dp_aux_dev *aux_dev = iocb->ki_filp->निजी_data;
	loff_t pos = iocb->ki_pos;
	sमाप_प्रकार res = 0;

	अगर (!atomic_inc_not_zero(&aux_dev->usecount))
		वापस -ENODEV;

	iov_iter_truncate(from, AUX_MAX_OFFSET - pos);

	जबतक (iov_iter_count(from)) अणु
		uपूर्णांक8_t buf[DP_AUX_MAX_PAYLOAD_BYTES];
		sमाप_प्रकार toकरो = min(iov_iter_count(from), माप(buf));

		अगर (संकेत_pending(current)) अणु
			res = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		अगर (!copy_from_iter_full(buf, toकरो, from)) अणु
			res = -EFAULT;
			अवरोध;
		पूर्ण

		res = drm_dp_dpcd_ग_लिखो(aux_dev->aux, pos, buf, toकरो);

		अगर (res <= 0)
			अवरोध;

		pos += res;
	पूर्ण

	अगर (pos != iocb->ki_pos)
		res = pos - iocb->ki_pos;
	iocb->ki_pos = pos;

	अगर (atomic_dec_and_test(&aux_dev->usecount))
		wake_up_var(&aux_dev->usecount);

	वापस res;
पूर्ण

अटल पूर्णांक auxdev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_dp_aux_dev *aux_dev = file->निजी_data;

	kref_put(&aux_dev->refcount, release_drm_dp_aux_dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations auxdev_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= auxdev_llseek,
	.पढ़ो_iter	= auxdev_पढ़ो_iter,
	.ग_लिखो_iter	= auxdev_ग_लिखो_iter,
	.खोलो		= auxdev_खोलो,
	.release	= auxdev_release,
पूर्ण;

#घोषणा to_auxdev(d) container_of(d, काष्ठा drm_dp_aux_dev, aux)

अटल काष्ठा drm_dp_aux_dev *drm_dp_aux_dev_get_by_aux(काष्ठा drm_dp_aux *aux)
अणु
	काष्ठा drm_dp_aux_dev *iter, *aux_dev = शून्य;
	पूर्णांक id;

	/* करोn't increase kref count here because this function should only be
	 * used by drm_dp_aux_unरेजिस्टर_devnode. Thus, it will always have at
	 * least one reference - the one that drm_dp_aux_रेजिस्टर_devnode
	 * created
	 */
	mutex_lock(&aux_idr_mutex);
	idr_क्रम_each_entry(&aux_idr, iter, id) अणु
		अगर (iter->aux == aux) अणु
			aux_dev = iter;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&aux_idr_mutex);
	वापस aux_dev;
पूर्ण

व्योम drm_dp_aux_unरेजिस्टर_devnode(काष्ठा drm_dp_aux *aux)
अणु
	काष्ठा drm_dp_aux_dev *aux_dev;
	अचिन्हित पूर्णांक minor;

	aux_dev = drm_dp_aux_dev_get_by_aux(aux);
	अगर (!aux_dev) /* attach must have failed */
		वापस;

	mutex_lock(&aux_idr_mutex);
	idr_हटाओ(&aux_idr, aux_dev->index);
	mutex_unlock(&aux_idr_mutex);

	atomic_dec(&aux_dev->usecount);
	रुको_var_event(&aux_dev->usecount, !atomic_पढ़ो(&aux_dev->usecount));

	minor = aux_dev->index;
	अगर (aux_dev->dev)
		device_destroy(drm_dp_aux_dev_class,
			       MKDEV(drm_dev_major, minor));

	DRM_DEBUG("drm_dp_aux_dev: aux [%s] unregistering\n", aux->name);
	kref_put(&aux_dev->refcount, release_drm_dp_aux_dev);
पूर्ण

पूर्णांक drm_dp_aux_रेजिस्टर_devnode(काष्ठा drm_dp_aux *aux)
अणु
	काष्ठा drm_dp_aux_dev *aux_dev;
	पूर्णांक res;

	aux_dev = alloc_drm_dp_aux_dev(aux);
	अगर (IS_ERR(aux_dev))
		वापस PTR_ERR(aux_dev);

	aux_dev->dev = device_create(drm_dp_aux_dev_class, aux->dev,
				     MKDEV(drm_dev_major, aux_dev->index), शून्य,
				     "drm_dp_aux%d", aux_dev->index);
	अगर (IS_ERR(aux_dev->dev)) अणु
		res = PTR_ERR(aux_dev->dev);
		aux_dev->dev = शून्य;
		जाओ error;
	पूर्ण

	DRM_DEBUG("drm_dp_aux_dev: aux [%s] registered as minor %d\n",
		  aux->name, aux_dev->index);
	वापस 0;
error:
	drm_dp_aux_unरेजिस्टर_devnode(aux);
	वापस res;
पूर्ण

पूर्णांक drm_dp_aux_dev_init(व्योम)
अणु
	पूर्णांक res;

	drm_dp_aux_dev_class = class_create(THIS_MODULE, "drm_dp_aux_dev");
	अगर (IS_ERR(drm_dp_aux_dev_class)) अणु
		वापस PTR_ERR(drm_dp_aux_dev_class);
	पूर्ण
	drm_dp_aux_dev_class->dev_groups = drm_dp_aux_groups;

	res = रेजिस्टर_chrdev(0, "aux", &auxdev_fops);
	अगर (res < 0)
		जाओ out;
	drm_dev_major = res;

	वापस 0;
out:
	class_destroy(drm_dp_aux_dev_class);
	वापस res;
पूर्ण

व्योम drm_dp_aux_dev_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev(drm_dev_major, "aux");
	class_destroy(drm_dp_aux_dev_class);
पूर्ण
