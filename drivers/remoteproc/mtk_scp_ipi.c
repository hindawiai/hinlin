<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2019 MediaTek Inc.

#समावेश <यंत्र/barrier.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/remoteproc/mtk_scp.h>

#समावेश "mtk_common.h"

/**
 * scp_ipi_रेजिस्टर() - रेजिस्टर an ipi function
 *
 * @scp:	mtk_scp काष्ठाure
 * @id:		IPI ID
 * @handler:	IPI handler
 * @priv:	निजी data क्रम IPI handler
 *
 * Register an ipi function to receive ipi पूर्णांकerrupt from SCP.
 *
 * Returns 0 अगर ipi रेजिस्टरs successfully, -error on error.
 */
पूर्णांक scp_ipi_रेजिस्टर(काष्ठा mtk_scp *scp,
		     u32 id,
		     scp_ipi_handler_t handler,
		     व्योम *priv)
अणु
	अगर (!scp)
		वापस -EPROBE_DEFER;

	अगर (WARN_ON(id >= SCP_IPI_MAX) || WARN_ON(handler == शून्य))
		वापस -EINVAL;

	scp_ipi_lock(scp, id);
	scp->ipi_desc[id].handler = handler;
	scp->ipi_desc[id].priv = priv;
	scp_ipi_unlock(scp, id);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(scp_ipi_रेजिस्टर);

/**
 * scp_ipi_unरेजिस्टर() - unरेजिस्टर an ipi function
 *
 * @scp:	mtk_scp काष्ठाure
 * @id:		IPI ID
 *
 * Unरेजिस्टर an ipi function to receive ipi पूर्णांकerrupt from SCP.
 */
व्योम scp_ipi_unरेजिस्टर(काष्ठा mtk_scp *scp, u32 id)
अणु
	अगर (!scp)
		वापस;

	अगर (WARN_ON(id >= SCP_IPI_MAX))
		वापस;

	scp_ipi_lock(scp, id);
	scp->ipi_desc[id].handler = शून्य;
	scp->ipi_desc[id].priv = शून्य;
	scp_ipi_unlock(scp, id);
पूर्ण
EXPORT_SYMBOL_GPL(scp_ipi_unरेजिस्टर);

/*
 * scp_स_नकल_aligned() - Copy src to dst, where dst is in SCP SRAM region.
 *
 * @dst:	Poपूर्णांकer to the destination buffer, should be in SCP SRAM region.
 * @src:	Poपूर्णांकer to the source buffer.
 * @len:	Length of the source buffer to be copied.
 *
 * Since AP access of SCP SRAM करोn't support byte ग_लिखो, this always ग_लिखो a
 * full word at a समय, and may cause some extra bytes to be written at the
 * beginning & ending of dst.
 */
व्योम scp_स_नकल_aligned(व्योम __iomem *dst, स्थिर व्योम *src, अचिन्हित पूर्णांक len)
अणु
	व्योम __iomem *ptr;
	u32 val;
	अचिन्हित पूर्णांक i = 0, reमुख्य;

	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)dst, 4)) अणु
		ptr = (व्योम __iomem *)ALIGN_DOWN((अचिन्हित दीर्घ)dst, 4);
		i = 4 - (dst - ptr);
		val = पढ़ोl_relaxed(ptr);
		स_नकल((u8 *)&val + (4 - i), src, i);
		ग_लिखोl_relaxed(val, ptr);
	पूर्ण

	__ioग_लिखो32_copy(dst + i, src + i, (len - i) / 4);
	reमुख्य = (len - i) % 4;

	अगर (reमुख्य > 0) अणु
		val = पढ़ोl_relaxed(dst + len - reमुख्य);
		स_नकल(&val, src + len - reमुख्य, reमुख्य);
		ग_लिखोl_relaxed(val, dst + len - reमुख्य);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(scp_स_नकल_aligned);

/**
 * scp_ipi_lock() - Lock beक्रमe operations of an IPI ID
 *
 * @scp:	mtk_scp काष्ठाure
 * @id:		IPI ID
 *
 * Note: This should not be used by drivers other than mtk_scp.
 */
व्योम scp_ipi_lock(काष्ठा mtk_scp *scp, u32 id)
अणु
	अगर (WARN_ON(id >= SCP_IPI_MAX))
		वापस;
	mutex_lock(&scp->ipi_desc[id].lock);
पूर्ण
EXPORT_SYMBOL_GPL(scp_ipi_lock);

/**
 * scp_ipi_lock() - Unlock after operations of an IPI ID
 *
 * @scp:	mtk_scp काष्ठाure
 * @id:		IPI ID
 *
 * Note: This should not be used by drivers other than mtk_scp.
 */
व्योम scp_ipi_unlock(काष्ठा mtk_scp *scp, u32 id)
अणु
	अगर (WARN_ON(id >= SCP_IPI_MAX))
		वापस;
	mutex_unlock(&scp->ipi_desc[id].lock);
पूर्ण
EXPORT_SYMBOL_GPL(scp_ipi_unlock);

/**
 * scp_ipi_send() - send data from AP to scp.
 *
 * @scp:	mtk_scp काष्ठाure
 * @id:		IPI ID
 * @buf:	the data buffer
 * @len:	the data buffer length
 * @रुको:	number of msecs to रुको क्रम ack. 0 to skip रुकोing.
 *
 * This function is thपढ़ो-safe. When this function वापसs,
 * SCP has received the data and starts the processing.
 * When the processing completes, IPI handler रेजिस्टरed
 * by scp_ipi_रेजिस्टर will be called in पूर्णांकerrupt context.
 *
 * Returns 0 अगर sending data successfully, -error on error.
 **/
पूर्णांक scp_ipi_send(काष्ठा mtk_scp *scp, u32 id, व्योम *buf, अचिन्हित पूर्णांक len,
		 अचिन्हित पूर्णांक रुको)
अणु
	काष्ठा mtk_share_obj __iomem *send_obj = scp->send_buf;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	अगर (WARN_ON(id <= SCP_IPI_INIT) || WARN_ON(id >= SCP_IPI_MAX) ||
	    WARN_ON(id == SCP_IPI_NS_SERVICE) ||
	    WARN_ON(len > माप(send_obj->share_buf)) || WARN_ON(!buf))
		वापस -EINVAL;

	mutex_lock(&scp->send_lock);

	ret = clk_prepare_enable(scp->clk);
	अगर (ret) अणु
		dev_err(scp->dev, "failed to enable clock\n");
		जाओ unlock_mutex;
	पूर्ण

	 /* Wait until SCP receives the last command */
	समयout = jअगरfies + msecs_to_jअगरfies(2000);
	करो अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(scp->dev, "%s: IPI timeout!\n", __func__);
			ret = -ETIMEDOUT;
			जाओ घड़ी_disable;
		पूर्ण
	पूर्ण जबतक (पढ़ोl(scp->reg_base + scp->data->host_to_scp_reg));

	scp_स_नकल_aligned(send_obj->share_buf, buf, len);

	ग_लिखोl(len, &send_obj->len);
	ग_लिखोl(id, &send_obj->id);

	scp->ipi_id_ack[id] = false;
	/* send the command to SCP */
	ग_लिखोl(scp->data->host_to_scp_पूर्णांक_bit,
	       scp->reg_base + scp->data->host_to_scp_reg);

	अगर (रुको) अणु
		/* रुको क्रम SCP's ACK */
		समयout = msecs_to_jअगरfies(रुको);
		ret = रुको_event_समयout(scp->ack_wq,
					 scp->ipi_id_ack[id],
					 समयout);
		scp->ipi_id_ack[id] = false;
		अगर (WARN(!ret, "scp ipi %d ack time out !", id))
			ret = -EIO;
		अन्यथा
			ret = 0;
	पूर्ण

घड़ी_disable:
	clk_disable_unprepare(scp->clk);
unlock_mutex:
	mutex_unlock(&scp->send_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(scp_ipi_send);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MediaTek scp IPI interface");
