<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 Pengutronix
 */

#अगर_अघोषित IMX_VDOA_H
#घोषणा IMX_VDOA_H

काष्ठा vकरोa_data;
काष्ठा vकरोa_ctx;

#अगर (defined CONFIG_VIDEO_IMX_VDOA || defined CONFIG_VIDEO_IMX_VDOA_MODULE)

काष्ठा vकरोa_ctx *vकरोa_context_create(काष्ठा vकरोa_data *vकरोa);
पूर्णांक vकरोa_context_configure(काष्ठा vकरोa_ctx *ctx,
			   अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
			   u32 pixelक्रमmat);
व्योम vकरोa_context_destroy(काष्ठा vकरोa_ctx *ctx);

व्योम vकरोa_device_run(काष्ठा vकरोa_ctx *ctx, dma_addr_t dst, dma_addr_t src);
पूर्णांक vकरोa_रुको_क्रम_completion(काष्ठा vकरोa_ctx *ctx);

#अन्यथा

अटल अंतरभूत काष्ठा vकरोa_ctx *vकरोa_context_create(काष्ठा vकरोa_data *vकरोa)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक vकरोa_context_configure(काष्ठा vकरोa_ctx *ctx,
					 अचिन्हित पूर्णांक width,
					 अचिन्हित पूर्णांक height,
					 u32 pixelक्रमmat)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम vकरोa_context_destroy(काष्ठा vकरोa_ctx *ctx) अणु पूर्ण;

अटल अंतरभूत व्योम vकरोa_device_run(काष्ठा vकरोa_ctx *ctx,
				   dma_addr_t dst, dma_addr_t src) अणु पूर्ण;

अटल अंतरभूत पूर्णांक vकरोa_रुको_क्रम_completion(काष्ठा vकरोa_ctx *ctx)
अणु
	वापस 0;
पूर्ण;

#पूर्ण_अगर

#पूर्ण_अगर /* IMX_VDOA_H */
