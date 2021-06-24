<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __IXP4XX_NPE_H
#घोषणा __IXP4XX_NPE_H

#समावेश <linux/kernel.h>

बाह्य स्थिर अक्षर *npe_names[];

काष्ठा npe_regs अणु
	u32 exec_addr, exec_data, exec_status_cmd, exec_count;
	u32 action_poपूर्णांकs[4];
	u32 watchpoपूर्णांक_fअगरo, watch_count;
	u32 profile_count;
	u32 messaging_status, messaging_control;
	u32 mailbox_status, /*messaging_*/ in_out_fअगरo;
पूर्ण;

काष्ठा npe अणु
	काष्ठा npe_regs __iomem *regs;
	पूर्णांक id;
	पूर्णांक valid;
पूर्ण;


अटल अंतरभूत स्थिर अक्षर *npe_name(काष्ठा npe *npe)
अणु
	वापस npe_names[npe->id];
पूर्ण

पूर्णांक npe_running(काष्ठा npe *npe);
पूर्णांक npe_send_message(काष्ठा npe *npe, स्थिर व्योम *msg, स्थिर अक्षर *what);
पूर्णांक npe_recv_message(काष्ठा npe *npe, व्योम *msg, स्थिर अक्षर *what);
पूर्णांक npe_send_recv_message(काष्ठा npe *npe, व्योम *msg, स्थिर अक्षर *what);
पूर्णांक npe_load_firmware(काष्ठा npe *npe, स्थिर अक्षर *name, काष्ठा device *dev);
काष्ठा npe *npe_request(अचिन्हित id);
व्योम npe_release(काष्ठा npe *npe);

#पूर्ण_अगर /* __IXP4XX_NPE_H */
