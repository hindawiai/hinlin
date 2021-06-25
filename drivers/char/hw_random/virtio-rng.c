<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ranकरोmness driver क्रम virtio
 *  Copyright (C) 2007, 2008 Rusty Russell IBM Corporation
 */

#समावेश <linux/err.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_rng.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

अटल DEFINE_IDA(rng_index_ida);

काष्ठा virtrng_info अणु
	काष्ठा hwrng hwrng;
	काष्ठा virtqueue *vq;
	काष्ठा completion have_data;
	अक्षर name[25];
	अचिन्हित पूर्णांक data_avail;
	पूर्णांक index;
	bool busy;
	bool hwrng_रेजिस्टर_करोne;
	bool hwrng_हटाओd;
पूर्ण;

अटल व्योम अक्रमom_recv_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtrng_info *vi = vq->vdev->priv;

	/* We can get spurious callbacks, e.g. shared IRQs + virtio_pci. */
	अगर (!virtqueue_get_buf(vi->vq, &vi->data_avail))
		वापस;

	complete(&vi->have_data);
पूर्ण

/* The host will fill any buffer we give it with sweet, sweet अक्रमomness. */
अटल व्योम रेजिस्टर_buffer(काष्ठा virtrng_info *vi, u8 *buf, माप_प्रकार size)
अणु
	काष्ठा scatterlist sg;

	sg_init_one(&sg, buf, size);

	/* There should always be room क्रम one buffer. */
	virtqueue_add_inbuf(vi->vq, &sg, 1, buf, GFP_KERNEL);

	virtqueue_kick(vi->vq);
पूर्ण

अटल पूर्णांक virtio_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार size, bool रुको)
अणु
	पूर्णांक ret;
	काष्ठा virtrng_info *vi = (काष्ठा virtrng_info *)rng->priv;

	अगर (vi->hwrng_हटाओd)
		वापस -ENODEV;

	अगर (!vi->busy) अणु
		vi->busy = true;
		reinit_completion(&vi->have_data);
		रेजिस्टर_buffer(vi, buf, size);
	पूर्ण

	अगर (!रुको)
		वापस 0;

	ret = रुको_क्रम_completion_समाप्तable(&vi->have_data);
	अगर (ret < 0)
		वापस ret;

	vi->busy = false;

	वापस vi->data_avail;
पूर्ण

अटल व्योम virtio_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा virtrng_info *vi = (काष्ठा virtrng_info *)rng->priv;

	अगर (vi->busy)
		रुको_क्रम_completion(&vi->have_data);
पूर्ण

अटल पूर्णांक probe_common(काष्ठा virtio_device *vdev)
अणु
	पूर्णांक err, index;
	काष्ठा virtrng_info *vi = शून्य;

	vi = kzalloc(माप(काष्ठा virtrng_info), GFP_KERNEL);
	अगर (!vi)
		वापस -ENOMEM;

	vi->index = index = ida_simple_get(&rng_index_ida, 0, 0, GFP_KERNEL);
	अगर (index < 0) अणु
		err = index;
		जाओ err_ida;
	पूर्ण
	प्र_लिखो(vi->name, "virtio_rng.%d", index);
	init_completion(&vi->have_data);

	vi->hwrng = (काष्ठा hwrng) अणु
		.पढ़ो = virtio_पढ़ो,
		.cleanup = virtio_cleanup,
		.priv = (अचिन्हित दीर्घ)vi,
		.name = vi->name,
		.quality = 1000,
	पूर्ण;
	vdev->priv = vi;

	/* We expect a single virtqueue. */
	vi->vq = virtio_find_single_vq(vdev, अक्रमom_recv_करोne, "input");
	अगर (IS_ERR(vi->vq)) अणु
		err = PTR_ERR(vi->vq);
		जाओ err_find;
	पूर्ण

	वापस 0;

err_find:
	ida_simple_हटाओ(&rng_index_ida, index);
err_ida:
	kमुक्त(vi);
	वापस err;
पूर्ण

अटल व्योम हटाओ_common(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtrng_info *vi = vdev->priv;

	vi->hwrng_हटाओd = true;
	vi->data_avail = 0;
	complete(&vi->have_data);
	vdev->config->reset(vdev);
	vi->busy = false;
	अगर (vi->hwrng_रेजिस्टर_करोne)
		hwrng_unरेजिस्टर(&vi->hwrng);
	vdev->config->del_vqs(vdev);
	ida_simple_हटाओ(&rng_index_ida, vi->index);
	kमुक्त(vi);
पूर्ण

अटल पूर्णांक virtrng_probe(काष्ठा virtio_device *vdev)
अणु
	वापस probe_common(vdev);
पूर्ण

अटल व्योम virtrng_हटाओ(काष्ठा virtio_device *vdev)
अणु
	हटाओ_common(vdev);
पूर्ण

अटल व्योम virtrng_scan(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtrng_info *vi = vdev->priv;
	पूर्णांक err;

	err = hwrng_रेजिस्टर(&vi->hwrng);
	अगर (!err)
		vi->hwrng_रेजिस्टर_करोne = true;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक virtrng_मुक्तze(काष्ठा virtio_device *vdev)
अणु
	हटाओ_common(vdev);
	वापस 0;
पूर्ण

अटल पूर्णांक virtrng_restore(काष्ठा virtio_device *vdev)
अणु
	पूर्णांक err;

	err = probe_common(vdev);
	अगर (!err) अणु
		काष्ठा virtrng_info *vi = vdev->priv;

		/*
		 * Set hwrng_हटाओd to ensure that virtio_पढ़ो()
		 * करोes not block रुकोing क्रम data beक्रमe the
		 * registration is complete.
		 */
		vi->hwrng_हटाओd = true;
		err = hwrng_रेजिस्टर(&vi->hwrng);
		अगर (!err) अणु
			vi->hwrng_रेजिस्टर_करोne = true;
			vi->hwrng_हटाओd = false;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_RNG, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा virtio_driver virtio_rng_driver = अणु
	.driver.name =	KBUILD_MODNAME,
	.driver.owner =	THIS_MODULE,
	.id_table =	id_table,
	.probe =	virtrng_probe,
	.हटाओ =	virtrng_हटाओ,
	.scan =		virtrng_scan,
#अगर_घोषित CONFIG_PM_SLEEP
	.मुक्तze =	virtrng_मुक्तze,
	.restore =	virtrng_restore,
#पूर्ण_अगर
पूर्ण;

module_virtio_driver(virtio_rng_driver);
MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("Virtio random number driver");
MODULE_LICENSE("GPL");
