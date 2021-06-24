<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * The On Chip Memory (OCMEM) allocator allows various clients to allocate
 * memory from OCMEM based on perक्रमmance, latency and घातer requirements.
 * This is typically used by the GPU, camera/video, and audio components on
 * some Snapdragon SoCs.
 *
 * Copyright (C) 2019 Brian Masney <masneyb@onstation.org>
 * Copyright (C) 2015 Red Hat. Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>

#अगर_अघोषित __OCMEM_H__
#घोषणा __OCMEM_H__

क्रमागत ocmem_client अणु
	/* GMEM clients */
	OCMEM_GRAPHICS = 0x0,
	/*
	 * TODO add more once ocmem_allocate() is clever enough to
	 * deal with multiple clients.
	 */
	OCMEM_CLIENT_MAX,
पूर्ण;

काष्ठा ocmem;

काष्ठा ocmem_buf अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ len;
पूर्ण;

#अगर IS_ENABLED(CONFIG_QCOM_OCMEM)

काष्ठा ocmem *of_get_ocmem(काष्ठा device *dev);
काष्ठा ocmem_buf *ocmem_allocate(काष्ठा ocmem *ocmem, क्रमागत ocmem_client client,
				 अचिन्हित दीर्घ size);
व्योम ocmem_मुक्त(काष्ठा ocmem *ocmem, क्रमागत ocmem_client client,
		काष्ठा ocmem_buf *buf);

#अन्यथा /* IS_ENABLED(CONFIG_QCOM_OCMEM) */

अटल अंतरभूत काष्ठा ocmem *of_get_ocmem(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा ocmem_buf *ocmem_allocate(काष्ठा ocmem *ocmem,
					       क्रमागत ocmem_client client,
					       अचिन्हित दीर्घ size)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम ocmem_मुक्त(काष्ठा ocmem *ocmem, क्रमागत ocmem_client client,
			      काष्ठा ocmem_buf *buf)
अणु
पूर्ण

#पूर्ण_अगर /* IS_ENABLED(CONFIG_QCOM_OCMEM) */

#पूर्ण_अगर /* __OCMEM_H__ */
