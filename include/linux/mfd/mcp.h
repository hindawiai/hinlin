<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/mfd/mcp.h
 *
 *  Copyright (C) 2001 Russell King, All Rights Reserved.
 */
#अगर_अघोषित MCP_H
#घोषणा MCP_H

#समावेश <linux/device.h>

काष्ठा mcp_ops;

काष्ठा mcp अणु
	काष्ठा module	*owner;
	काष्ठा mcp_ops	*ops;
	spinlock_t	lock;
	पूर्णांक		use_count;
	अचिन्हित पूर्णांक	sclk_rate;
	अचिन्हित पूर्णांक	rw_समयout;
	काष्ठा device	attached_device;
पूर्ण;

काष्ठा mcp_ops अणु
	व्योम		(*set_telecom_भागisor)(काष्ठा mcp *, अचिन्हित पूर्णांक);
	व्योम		(*set_audio_भागisor)(काष्ठा mcp *, अचिन्हित पूर्णांक);
	व्योम		(*reg_ग_लिखो)(काष्ठा mcp *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
	अचिन्हित पूर्णांक	(*reg_पढ़ो)(काष्ठा mcp *, अचिन्हित पूर्णांक);
	व्योम		(*enable)(काष्ठा mcp *);
	व्योम		(*disable)(काष्ठा mcp *);
पूर्ण;

व्योम mcp_set_telecom_भागisor(काष्ठा mcp *, अचिन्हित पूर्णांक);
व्योम mcp_set_audio_भागisor(काष्ठा mcp *, अचिन्हित पूर्णांक);
व्योम mcp_reg_ग_लिखो(काष्ठा mcp *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
अचिन्हित पूर्णांक mcp_reg_पढ़ो(काष्ठा mcp *, अचिन्हित पूर्णांक);
व्योम mcp_enable(काष्ठा mcp *);
व्योम mcp_disable(काष्ठा mcp *);
#घोषणा mcp_get_sclk_rate(mcp)	((mcp)->sclk_rate)

काष्ठा mcp *mcp_host_alloc(काष्ठा device *, माप_प्रकार);
पूर्णांक mcp_host_add(काष्ठा mcp *, व्योम *);
व्योम mcp_host_del(काष्ठा mcp *);
व्योम mcp_host_मुक्त(काष्ठा mcp *);

काष्ठा mcp_driver अणु
	काष्ठा device_driver drv;
	पूर्णांक (*probe)(काष्ठा mcp *);
	व्योम (*हटाओ)(काष्ठा mcp *);
पूर्ण;

पूर्णांक mcp_driver_रेजिस्टर(काष्ठा mcp_driver *);
व्योम mcp_driver_unरेजिस्टर(काष्ठा mcp_driver *);

#घोषणा mcp_get_drvdata(mcp)	dev_get_drvdata(&(mcp)->attached_device)
#घोषणा mcp_set_drvdata(mcp,d)	dev_set_drvdata(&(mcp)->attached_device, d)

अटल अंतरभूत व्योम *mcp_priv(काष्ठा mcp *mcp)
अणु
	वापस mcp + 1;
पूर्ण

#पूर्ण_अगर
