<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016-2017, Linaro Ltd
 */

#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mailbox_client.h>

#समावेश "rpmsg_internal.h"
#समावेश "qcom_glink_native.h"

#घोषणा RPM_TOC_SIZE		256
#घोषणा RPM_TOC_MAGIC		0x67727430 /* grt0 */
#घोषणा RPM_TOC_MAX_ENTRIES	((RPM_TOC_SIZE - माप(काष्ठा rpm_toc)) / \
				 माप(काष्ठा rpm_toc_entry))

#घोषणा RPM_TX_FIFO_ID		0x61703272 /* ap2r */
#घोषणा RPM_RX_FIFO_ID		0x72326170 /* r2ap */

#घोषणा to_rpm_pipe(p) container_of(p, काष्ठा glink_rpm_pipe, native)

काष्ठा rpm_toc_entry अणु
	__le32 id;
	__le32 offset;
	__le32 size;
पूर्ण __packed;

काष्ठा rpm_toc अणु
	__le32 magic;
	__le32 count;

	काष्ठा rpm_toc_entry entries[];
पूर्ण __packed;

काष्ठा glink_rpm_pipe अणु
	काष्ठा qcom_glink_pipe native;

	व्योम __iomem *tail;
	व्योम __iomem *head;

	व्योम __iomem *fअगरo;
पूर्ण;

अटल माप_प्रकार glink_rpm_rx_avail(काष्ठा qcom_glink_pipe *glink_pipe)
अणु
	काष्ठा glink_rpm_pipe *pipe = to_rpm_pipe(glink_pipe);
	अचिन्हित पूर्णांक head;
	अचिन्हित पूर्णांक tail;

	head = पढ़ोl(pipe->head);
	tail = पढ़ोl(pipe->tail);

	अगर (head < tail)
		वापस pipe->native.length - tail + head;
	अन्यथा
		वापस head - tail;
पूर्ण

अटल व्योम glink_rpm_rx_peak(काष्ठा qcom_glink_pipe *glink_pipe,
			      व्योम *data, अचिन्हित पूर्णांक offset, माप_प्रकार count)
अणु
	काष्ठा glink_rpm_pipe *pipe = to_rpm_pipe(glink_pipe);
	अचिन्हित पूर्णांक tail;
	माप_प्रकार len;

	tail = पढ़ोl(pipe->tail);
	tail += offset;
	अगर (tail >= pipe->native.length)
		tail -= pipe->native.length;

	len = min_t(माप_प्रकार, count, pipe->native.length - tail);
	अगर (len) अणु
		__ioपढ़ो32_copy(data, pipe->fअगरo + tail,
				len / माप(u32));
	पूर्ण

	अगर (len != count) अणु
		__ioपढ़ो32_copy(data + len, pipe->fअगरo,
				(count - len) / माप(u32));
	पूर्ण
पूर्ण

अटल व्योम glink_rpm_rx_advance(काष्ठा qcom_glink_pipe *glink_pipe,
				 माप_प्रकार count)
अणु
	काष्ठा glink_rpm_pipe *pipe = to_rpm_pipe(glink_pipe);
	अचिन्हित पूर्णांक tail;

	tail = पढ़ोl(pipe->tail);

	tail += count;
	अगर (tail >= pipe->native.length)
		tail -= pipe->native.length;

	ग_लिखोl(tail, pipe->tail);
पूर्ण

अटल माप_प्रकार glink_rpm_tx_avail(काष्ठा qcom_glink_pipe *glink_pipe)
अणु
	काष्ठा glink_rpm_pipe *pipe = to_rpm_pipe(glink_pipe);
	अचिन्हित पूर्णांक head;
	अचिन्हित पूर्णांक tail;

	head = पढ़ोl(pipe->head);
	tail = पढ़ोl(pipe->tail);

	अगर (tail <= head)
		वापस pipe->native.length - head + tail;
	अन्यथा
		वापस tail - head;
पूर्ण

अटल अचिन्हित पूर्णांक glink_rpm_tx_ग_लिखो_one(काष्ठा glink_rpm_pipe *pipe,
					   अचिन्हित पूर्णांक head,
					   स्थिर व्योम *data, माप_प्रकार count)
अणु
	माप_प्रकार len;

	len = min_t(माप_प्रकार, count, pipe->native.length - head);
	अगर (len) अणु
		__ioग_लिखो32_copy(pipe->fअगरo + head, data,
				 len / माप(u32));
	पूर्ण

	अगर (len != count) अणु
		__ioग_लिखो32_copy(pipe->fअगरo, data + len,
				 (count - len) / माप(u32));
	पूर्ण

	head += count;
	अगर (head >= pipe->native.length)
		head -= pipe->native.length;

	वापस head;
पूर्ण

अटल व्योम glink_rpm_tx_ग_लिखो(काष्ठा qcom_glink_pipe *glink_pipe,
			       स्थिर व्योम *hdr, माप_प्रकार hlen,
			       स्थिर व्योम *data, माप_प्रकार dlen)
अणु
	काष्ठा glink_rpm_pipe *pipe = to_rpm_pipe(glink_pipe);
	माप_प्रकार tlen = hlen + dlen;
	माप_प्रकार aligned_dlen;
	अचिन्हित पूर्णांक head;
	अक्षर padding[8] = अणु0पूर्ण;
	माप_प्रकार pad;

	/* Header length comes from glink native and is always 4 byte aligned */
	अगर (WARN(hlen % 4, "Glink Header length must be 4 bytes aligned\n"))
		वापस;

	/*
	 * Move the unaligned tail of the message to the padding chunk, to
	 * ensure word aligned accesses
	 */
	aligned_dlen = ALIGN_DOWN(dlen, 4);
	अगर (aligned_dlen != dlen)
		स_नकल(padding, data + aligned_dlen, dlen - aligned_dlen);

	head = पढ़ोl(pipe->head);
	head = glink_rpm_tx_ग_लिखो_one(pipe, head, hdr, hlen);
	head = glink_rpm_tx_ग_लिखो_one(pipe, head, data, aligned_dlen);

	pad = ALIGN(tlen, 8) - ALIGN_DOWN(tlen, 4);
	अगर (pad)
		head = glink_rpm_tx_ग_लिखो_one(pipe, head, padding, pad);
	ग_लिखोl(head, pipe->head);
पूर्ण

अटल पूर्णांक glink_rpm_parse_toc(काष्ठा device *dev,
			       व्योम __iomem *msg_ram,
			       माप_प्रकार msg_ram_size,
			       काष्ठा glink_rpm_pipe *rx,
			       काष्ठा glink_rpm_pipe *tx)
अणु
	काष्ठा rpm_toc *toc;
	पूर्णांक num_entries;
	अचिन्हित पूर्णांक id;
	माप_प्रकार offset;
	माप_प्रकार size;
	व्योम *buf;
	पूर्णांक i;

	buf = kzalloc(RPM_TOC_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	__ioपढ़ो32_copy(buf, msg_ram + msg_ram_size - RPM_TOC_SIZE,
			RPM_TOC_SIZE / माप(u32));

	toc = buf;

	अगर (le32_to_cpu(toc->magic) != RPM_TOC_MAGIC) अणु
		dev_err(dev, "RPM TOC has invalid magic\n");
		जाओ err_inval;
	पूर्ण

	num_entries = le32_to_cpu(toc->count);
	अगर (num_entries > RPM_TOC_MAX_ENTRIES) अणु
		dev_err(dev, "Invalid number of toc entries\n");
		जाओ err_inval;
	पूर्ण

	क्रम (i = 0; i < num_entries; i++) अणु
		id = le32_to_cpu(toc->entries[i].id);
		offset = le32_to_cpu(toc->entries[i].offset);
		size = le32_to_cpu(toc->entries[i].size);

		अगर (offset > msg_ram_size || offset + size > msg_ram_size) अणु
			dev_err(dev, "TOC entry with invalid size\n");
			जारी;
		पूर्ण

		चयन (id) अणु
		हाल RPM_RX_FIFO_ID:
			rx->native.length = size;

			rx->tail = msg_ram + offset;
			rx->head = msg_ram + offset + माप(u32);
			rx->fअगरo = msg_ram + offset + 2 * माप(u32);
			अवरोध;
		हाल RPM_TX_FIFO_ID:
			tx->native.length = size;

			tx->tail = msg_ram + offset;
			tx->head = msg_ram + offset + माप(u32);
			tx->fअगरo = msg_ram + offset + 2 * माप(u32);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!rx->fअगरo || !tx->fअगरo) अणु
		dev_err(dev, "Unable to find rx and tx descriptors\n");
		जाओ err_inval;
	पूर्ण

	kमुक्त(buf);
	वापस 0;

err_inval:
	kमुक्त(buf);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक glink_rpm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_glink *glink;
	काष्ठा glink_rpm_pipe *rx_pipe;
	काष्ठा glink_rpm_pipe *tx_pipe;
	काष्ठा device_node *np;
	व्योम __iomem *msg_ram;
	माप_प्रकार msg_ram_size;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource r;
	पूर्णांक ret;

	rx_pipe = devm_kzalloc(&pdev->dev, माप(*rx_pipe), GFP_KERNEL);
	tx_pipe = devm_kzalloc(&pdev->dev, माप(*tx_pipe), GFP_KERNEL);
	अगर (!rx_pipe || !tx_pipe)
		वापस -ENOMEM;

	np = of_parse_phandle(dev->of_node, "qcom,rpm-msg-ram", 0);
	ret = of_address_to_resource(np, 0, &r);
	of_node_put(np);
	अगर (ret)
		वापस ret;

	msg_ram = devm_ioremap(dev, r.start, resource_size(&r));
	msg_ram_size = resource_size(&r);
	अगर (!msg_ram)
		वापस -ENOMEM;

	ret = glink_rpm_parse_toc(dev, msg_ram, msg_ram_size,
				  rx_pipe, tx_pipe);
	अगर (ret)
		वापस ret;

	/* Pipe specअगरic accessors */
	rx_pipe->native.avail = glink_rpm_rx_avail;
	rx_pipe->native.peak = glink_rpm_rx_peak;
	rx_pipe->native.advance = glink_rpm_rx_advance;
	tx_pipe->native.avail = glink_rpm_tx_avail;
	tx_pipe->native.ग_लिखो = glink_rpm_tx_ग_लिखो;

	ग_लिखोl(0, tx_pipe->head);
	ग_लिखोl(0, rx_pipe->tail);

	glink = qcom_glink_native_probe(&pdev->dev,
					0,
					&rx_pipe->native,
					&tx_pipe->native,
					true);
	अगर (IS_ERR(glink))
		वापस PTR_ERR(glink);

	platक्रमm_set_drvdata(pdev, glink);

	वापस 0;
पूर्ण

अटल पूर्णांक glink_rpm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_glink *glink = platक्रमm_get_drvdata(pdev);

	qcom_glink_native_हटाओ(glink);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id glink_rpm_of_match[] = अणु
	अणु .compatible = "qcom,glink-rpm" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, glink_rpm_of_match);

अटल काष्ठा platक्रमm_driver glink_rpm_driver = अणु
	.probe = glink_rpm_probe,
	.हटाओ = glink_rpm_हटाओ,
	.driver = अणु
		.name = "qcom_glink_rpm",
		.of_match_table = glink_rpm_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init glink_rpm_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&glink_rpm_driver);
पूर्ण
subsys_initcall(glink_rpm_init);

अटल व्योम __निकास glink_rpm_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&glink_rpm_driver);
पूर्ण
module_निकास(glink_rpm_निकास);

MODULE_AUTHOR("Bjorn Andersson <bjorn.andersson@linaro.org>");
MODULE_DESCRIPTION("Qualcomm GLINK RPM driver");
MODULE_LICENSE("GPL v2");
