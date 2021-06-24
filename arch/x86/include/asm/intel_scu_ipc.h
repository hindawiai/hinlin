<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_INTEL_SCU_IPC_H_
#घोषणा  _ASM_X86_INTEL_SCU_IPC_H_

#समावेश <linux/ioport.h>

काष्ठा device;
काष्ठा पूर्णांकel_scu_ipc_dev;

/**
 * काष्ठा पूर्णांकel_scu_ipc_data - Data used to configure SCU IPC
 * @mem: Base address of SCU IPC MMIO रेजिस्टरs
 * @irq: The IRQ number used क्रम SCU (optional)
 */
काष्ठा पूर्णांकel_scu_ipc_data अणु
	काष्ठा resource mem;
	पूर्णांक irq;
पूर्ण;

काष्ठा पूर्णांकel_scu_ipc_dev *
__पूर्णांकel_scu_ipc_रेजिस्टर(काष्ठा device *parent,
			 स्थिर काष्ठा पूर्णांकel_scu_ipc_data *scu_data,
			 काष्ठा module *owner);

#घोषणा पूर्णांकel_scu_ipc_रेजिस्टर(parent, scu_data)  \
	__पूर्णांकel_scu_ipc_रेजिस्टर(parent, scu_data, THIS_MODULE)

व्योम पूर्णांकel_scu_ipc_unरेजिस्टर(काष्ठा पूर्णांकel_scu_ipc_dev *scu);

काष्ठा पूर्णांकel_scu_ipc_dev *
__devm_पूर्णांकel_scu_ipc_रेजिस्टर(काष्ठा device *parent,
			      स्थिर काष्ठा पूर्णांकel_scu_ipc_data *scu_data,
			      काष्ठा module *owner);

#घोषणा devm_पूर्णांकel_scu_ipc_रेजिस्टर(parent, scu_data)  \
	__devm_पूर्णांकel_scu_ipc_रेजिस्टर(parent, scu_data, THIS_MODULE)

काष्ठा पूर्णांकel_scu_ipc_dev *पूर्णांकel_scu_ipc_dev_get(व्योम);
व्योम पूर्णांकel_scu_ipc_dev_put(काष्ठा पूर्णांकel_scu_ipc_dev *scu);
काष्ठा पूर्णांकel_scu_ipc_dev *devm_पूर्णांकel_scu_ipc_dev_get(काष्ठा device *dev);

पूर्णांक पूर्णांकel_scu_ipc_dev_ioपढ़ो8(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u16 addr,
			      u8 *data);
पूर्णांक पूर्णांकel_scu_ipc_dev_ioग_लिखो8(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u16 addr,
			       u8 data);
पूर्णांक पूर्णांकel_scu_ipc_dev_पढ़ोv(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u16 *addr,
			    u8 *data, माप_प्रकार len);
पूर्णांक पूर्णांकel_scu_ipc_dev_ग_लिखोv(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u16 *addr,
			     u8 *data, माप_प्रकार len);

पूर्णांक पूर्णांकel_scu_ipc_dev_update(काष्ठा पूर्णांकel_scu_ipc_dev *scu, u16 addr,
			     u8 data, u8 mask);

पूर्णांक पूर्णांकel_scu_ipc_dev_simple_command(काष्ठा पूर्णांकel_scu_ipc_dev *scu, पूर्णांक cmd,
				     पूर्णांक sub);
पूर्णांक पूर्णांकel_scu_ipc_dev_command_with_size(काष्ठा पूर्णांकel_scu_ipc_dev *scu, पूर्णांक cmd,
					पूर्णांक sub, स्थिर व्योम *in, माप_प्रकार inlen,
					माप_प्रकार size, व्योम *out, माप_प्रकार outlen);

अटल अंतरभूत पूर्णांक पूर्णांकel_scu_ipc_dev_command(काष्ठा पूर्णांकel_scu_ipc_dev *scu, पूर्णांक cmd,
					    पूर्णांक sub, स्थिर व्योम *in, माप_प्रकार inlen,
					    व्योम *out, माप_प्रकार outlen)
अणु
	वापस पूर्णांकel_scu_ipc_dev_command_with_size(scu, cmd, sub, in, inlen,
						   inlen, out, outlen);
पूर्ण

#पूर्ण_अगर
