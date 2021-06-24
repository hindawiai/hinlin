<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * rcar-fcp.h  --  R-Car Frame Compression Processor Driver
 *
 * Copyright (C) 2016 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __MEDIA_RCAR_FCP_H__
#घोषणा __MEDIA_RCAR_FCP_H__

काष्ठा device_node;
काष्ठा rcar_fcp_device;

#अगर IS_ENABLED(CONFIG_VIDEO_RENESAS_FCP)
काष्ठा rcar_fcp_device *rcar_fcp_get(स्थिर काष्ठा device_node *np);
व्योम rcar_fcp_put(काष्ठा rcar_fcp_device *fcp);
काष्ठा device *rcar_fcp_get_device(काष्ठा rcar_fcp_device *fcp);
पूर्णांक rcar_fcp_enable(काष्ठा rcar_fcp_device *fcp);
व्योम rcar_fcp_disable(काष्ठा rcar_fcp_device *fcp);
#अन्यथा
अटल अंतरभूत काष्ठा rcar_fcp_device *rcar_fcp_get(स्थिर काष्ठा device_node *np)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
अटल अंतरभूत व्योम rcar_fcp_put(काष्ठा rcar_fcp_device *fcp) अणु पूर्ण
अटल अंतरभूत काष्ठा device *rcar_fcp_get_device(काष्ठा rcar_fcp_device *fcp)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक rcar_fcp_enable(काष्ठा rcar_fcp_device *fcp)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम rcar_fcp_disable(काष्ठा rcar_fcp_device *fcp) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MEDIA_RCAR_FCP_H__ */
