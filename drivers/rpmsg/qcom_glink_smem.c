<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016, Linaro Ltd
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/slab.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/idr.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/soc/qcom/sस्मृति.स>
#समावेश <linux/sizes.h>
#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/list.h>

#समावेश <linux/rpmsg/qcom_glink.h>

#समावेश "qcom_glink_native.h"

#घोषणा FIFO_FULL_RESERVE 8
#घोषणा FIFO_ALIGNMENT 8
#घोषणा TX_BLOCKED_CMD_RESERVE 8 /* size of काष्ठा पढ़ो_notअगर_request */

#घोषणा SMEM_GLINK_NATIVE_XPRT_DESCRIPTOR	478
#घोषणा SMEM_GLINK_NATIVE_XPRT_FIFO_0		479
#घोषणा SMEM_GLINK_NATIVE_XPRT_FIFO_1		480

काष्ठा glink_smem_pipe अणु
	काष्ठा qcom_glink_pipe native;

	__le32 *tail;
	__le32 *head;

	व्योम *fअगरo;

	पूर्णांक remote_pid;
पूर्ण;

#घोषणा to_smem_pipe(p) container_of(p, काष्ठा glink_smem_pipe, native)

अटल माप_प्रकार glink_smem_rx_avail(काष्ठा qcom_glink_pipe *np)
अणु
	काष्ठा glink_smem_pipe *pipe = to_smem_pipe(np);
	माप_प्रकार len;
	व्योम *fअगरo;
	u32 head;
	u32 tail;

	अगर (!pipe->fअगरo) अणु
		fअगरo = qcom_smem_get(pipe->remote_pid,
				     SMEM_GLINK_NATIVE_XPRT_FIFO_1, &len);
		अगर (IS_ERR(fअगरo)) अणु
			pr_err("failed to acquire RX fifo handle: %ld\n",
			       PTR_ERR(fअगरo));
			वापस 0;
		पूर्ण

		pipe->fअगरo = fअगरo;
		pipe->native.length = len;
	पूर्ण

	head = le32_to_cpu(*pipe->head);
	tail = le32_to_cpu(*pipe->tail);

	अगर (head < tail)
		वापस pipe->native.length - tail + head;
	अन्यथा
		वापस head - tail;
पूर्ण

अटल व्योम glink_smem_rx_peak(काष्ठा qcom_glink_pipe *np,
			       व्योम *data, अचिन्हित पूर्णांक offset, माप_प्रकार count)
अणु
	काष्ठा glink_smem_pipe *pipe = to_smem_pipe(np);
	माप_प्रकार len;
	u32 tail;

	tail = le32_to_cpu(*pipe->tail);
	tail += offset;
	अगर (tail >= pipe->native.length)
		tail -= pipe->native.length;

	len = min_t(माप_प्रकार, count, pipe->native.length - tail);
	अगर (len)
		स_नकल_fromio(data, pipe->fअगरo + tail, len);

	अगर (len != count)
		स_नकल_fromio(data + len, pipe->fअगरo, (count - len));
पूर्ण

अटल व्योम glink_smem_rx_advance(काष्ठा qcom_glink_pipe *np,
				  माप_प्रकार count)
अणु
	काष्ठा glink_smem_pipe *pipe = to_smem_pipe(np);
	u32 tail;

	tail = le32_to_cpu(*pipe->tail);

	tail += count;
	अगर (tail >= pipe->native.length)
		tail -= pipe->native.length;

	*pipe->tail = cpu_to_le32(tail);
पूर्ण

अटल माप_प्रकार glink_smem_tx_avail(काष्ठा qcom_glink_pipe *np)
अणु
	काष्ठा glink_smem_pipe *pipe = to_smem_pipe(np);
	u32 head;
	u32 tail;
	u32 avail;

	head = le32_to_cpu(*pipe->head);
	tail = le32_to_cpu(*pipe->tail);

	अगर (tail <= head)
		avail = pipe->native.length - head + tail;
	अन्यथा
		avail = tail - head;

	अगर (avail < (FIFO_FULL_RESERVE + TX_BLOCKED_CMD_RESERVE))
		avail = 0;
	अन्यथा
		avail -= FIFO_FULL_RESERVE + TX_BLOCKED_CMD_RESERVE;

	वापस avail;
पूर्ण

अटल अचिन्हित पूर्णांक glink_smem_tx_ग_लिखो_one(काष्ठा glink_smem_pipe *pipe,
					    अचिन्हित पूर्णांक head,
					    स्थिर व्योम *data, माप_प्रकार count)
अणु
	माप_प्रकार len;

	len = min_t(माप_प्रकार, count, pipe->native.length - head);
	अगर (len)
		स_नकल(pipe->fअगरo + head, data, len);

	अगर (len != count)
		स_नकल(pipe->fअगरo, data + len, count - len);

	head += count;
	अगर (head >= pipe->native.length)
		head -= pipe->native.length;

	वापस head;
पूर्ण

अटल व्योम glink_smem_tx_ग_लिखो(काष्ठा qcom_glink_pipe *glink_pipe,
				स्थिर व्योम *hdr, माप_प्रकार hlen,
				स्थिर व्योम *data, माप_प्रकार dlen)
अणु
	काष्ठा glink_smem_pipe *pipe = to_smem_pipe(glink_pipe);
	अचिन्हित पूर्णांक head;

	head = le32_to_cpu(*pipe->head);

	head = glink_smem_tx_ग_लिखो_one(pipe, head, hdr, hlen);
	head = glink_smem_tx_ग_लिखो_one(pipe, head, data, dlen);

	/* Ensure head is always aligned to 8 bytes */
	head = ALIGN(head, 8);
	अगर (head >= pipe->native.length)
		head -= pipe->native.length;

	/* Ensure ordering of fअगरo and head update */
	wmb();

	*pipe->head = cpu_to_le32(head);
पूर्ण

अटल व्योम qcom_glink_smem_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

काष्ठा qcom_glink *qcom_glink_smem_रेजिस्टर(काष्ठा device *parent,
					    काष्ठा device_node *node)
अणु
	काष्ठा glink_smem_pipe *rx_pipe;
	काष्ठा glink_smem_pipe *tx_pipe;
	काष्ठा qcom_glink *glink;
	काष्ठा device *dev;
	u32 remote_pid;
	__le32 *descs;
	माप_प्रकार size;
	पूर्णांक ret;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	dev->parent = parent;
	dev->of_node = node;
	dev->release = qcom_glink_smem_release;
	dev_set_name(dev, "%s:%pOFn", dev_name(parent->parent), node);
	ret = device_रेजिस्टर(dev);
	अगर (ret) अणु
		pr_err("failed to register glink edge\n");
		put_device(dev);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "qcom,remote-pid",
				   &remote_pid);
	अगर (ret) अणु
		dev_err(dev, "failed to parse qcom,remote-pid\n");
		जाओ err_put_dev;
	पूर्ण

	rx_pipe = devm_kzalloc(dev, माप(*rx_pipe), GFP_KERNEL);
	tx_pipe = devm_kzalloc(dev, माप(*tx_pipe), GFP_KERNEL);
	अगर (!rx_pipe || !tx_pipe) अणु
		ret = -ENOMEM;
		जाओ err_put_dev;
	पूर्ण

	ret = qcom_smem_alloc(remote_pid,
			      SMEM_GLINK_NATIVE_XPRT_DESCRIPTOR, 32);
	अगर (ret && ret != -EEXIST) अणु
		dev_err(dev, "failed to allocate glink descriptors\n");
		जाओ err_put_dev;
	पूर्ण

	descs = qcom_smem_get(remote_pid,
			      SMEM_GLINK_NATIVE_XPRT_DESCRIPTOR, &size);
	अगर (IS_ERR(descs)) अणु
		dev_err(dev, "failed to acquire xprt descriptor\n");
		ret = PTR_ERR(descs);
		जाओ err_put_dev;
	पूर्ण

	अगर (size != 32) अणु
		dev_err(dev, "glink descriptor of invalid size\n");
		ret = -EINVAL;
		जाओ err_put_dev;
	पूर्ण

	tx_pipe->tail = &descs[0];
	tx_pipe->head = &descs[1];
	rx_pipe->tail = &descs[2];
	rx_pipe->head = &descs[3];

	ret = qcom_smem_alloc(remote_pid, SMEM_GLINK_NATIVE_XPRT_FIFO_0,
			      SZ_16K);
	अगर (ret && ret != -EEXIST) अणु
		dev_err(dev, "failed to allocate TX fifo\n");
		जाओ err_put_dev;
	पूर्ण

	tx_pipe->fअगरo = qcom_smem_get(remote_pid, SMEM_GLINK_NATIVE_XPRT_FIFO_0,
				      &tx_pipe->native.length);
	अगर (IS_ERR(tx_pipe->fअगरo)) अणु
		dev_err(dev, "failed to acquire TX fifo\n");
		ret = PTR_ERR(tx_pipe->fअगरo);
		जाओ err_put_dev;
	पूर्ण

	rx_pipe->native.avail = glink_smem_rx_avail;
	rx_pipe->native.peak = glink_smem_rx_peak;
	rx_pipe->native.advance = glink_smem_rx_advance;
	rx_pipe->remote_pid = remote_pid;

	tx_pipe->native.avail = glink_smem_tx_avail;
	tx_pipe->native.ग_लिखो = glink_smem_tx_ग_लिखो;
	tx_pipe->remote_pid = remote_pid;

	*rx_pipe->tail = 0;
	*tx_pipe->head = 0;

	glink = qcom_glink_native_probe(dev,
					GLINK_FEATURE_INTENT_REUSE,
					&rx_pipe->native, &tx_pipe->native,
					false);
	अगर (IS_ERR(glink)) अणु
		ret = PTR_ERR(glink);
		जाओ err_put_dev;
	पूर्ण

	वापस glink;

err_put_dev:
	device_unरेजिस्टर(dev);

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_glink_smem_रेजिस्टर);

व्योम qcom_glink_smem_unरेजिस्टर(काष्ठा qcom_glink *glink)
अणु
	qcom_glink_native_हटाओ(glink);
	qcom_glink_native_unरेजिस्टर(glink);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_glink_smem_unरेजिस्टर);

MODULE_AUTHOR("Bjorn Andersson <bjorn.andersson@linaro.org>");
MODULE_DESCRIPTION("Qualcomm GLINK SMEM driver");
MODULE_LICENSE("GPL v2");
