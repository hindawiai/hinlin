<शैली गुरु>
#अगर_अघोषित __NVKM_FALCON_H__
#घोषणा __NVKM_FALCON_H__
#समावेश <engine/falcon.h>

पूर्णांक nvkm_falcon_ctor(स्थिर काष्ठा nvkm_falcon_func *, काष्ठा nvkm_subdev *owner,
		     स्थिर अक्षर *name, u32 addr, काष्ठा nvkm_falcon *);
व्योम nvkm_falcon_dtor(काष्ठा nvkm_falcon *);

व्योम nvkm_falcon_v1_load_imem(काष्ठा nvkm_falcon *,
			      व्योम *, u32, u32, u16, u8, bool);
व्योम nvkm_falcon_v1_load_dmem(काष्ठा nvkm_falcon *, व्योम *, u32, u32, u8);
व्योम nvkm_falcon_v1_पढ़ो_dmem(काष्ठा nvkm_falcon *, u32, u32, u8, व्योम *);
व्योम nvkm_falcon_v1_bind_context(काष्ठा nvkm_falcon *, काष्ठा nvkm_memory *);
पूर्णांक nvkm_falcon_v1_रुको_क्रम_halt(काष्ठा nvkm_falcon *, u32);
पूर्णांक nvkm_falcon_v1_clear_पूर्णांकerrupt(काष्ठा nvkm_falcon *, u32);
व्योम nvkm_falcon_v1_set_start_addr(काष्ठा nvkm_falcon *, u32 start_addr);
व्योम nvkm_falcon_v1_start(काष्ठा nvkm_falcon *);
पूर्णांक nvkm_falcon_v1_enable(काष्ठा nvkm_falcon *);
व्योम nvkm_falcon_v1_disable(काष्ठा nvkm_falcon *);

व्योम gp102_sec2_flcn_bind_context(काष्ठा nvkm_falcon *, काष्ठा nvkm_memory *);
पूर्णांक gp102_sec2_flcn_enable(काष्ठा nvkm_falcon *);

#घोषणा FLCN_PRINTK(t,f,fmt,a...) करो अणु                               \
	अगर ((f)->owner->name != (f)->name)                           \
		nvkm_##t((f)->owner, "%s: "fmt"\n", (f)->name, ##a); \
	अन्यथा                                                         \
		nvkm_##t((f)->owner, fmt"\n", ##a);                  \
पूर्ण जबतक(0)
#घोषणा FLCN_DBG(f,fmt,a...) FLCN_PRINTK(debug, (f), fmt, ##a)
#घोषणा FLCN_ERR(f,fmt,a...) FLCN_PRINTK(error, (f), fmt, ##a)

/**
 * काष्ठा nvfw_falcon_msg - header क्रम all messages
 *
 * @unit_id:	id of firmware process that sent the message
 * @size:	total size of message
 * @ctrl_flags:	control flags
 * @seq_id:	used to match a message from its corresponding command
 */
काष्ठा nvfw_falcon_msg अणु
	u8 unit_id;
	u8 size;
	u8 ctrl_flags;
	u8 seq_id;
पूर्ण;

#घोषणा nvfw_falcon_cmd nvfw_falcon_msg
#घोषणा NV_FALCON_CMD_UNIT_ID_REWIND                                       0x00

काष्ठा nvkm_falcon_qmgr;
पूर्णांक nvkm_falcon_qmgr_new(काष्ठा nvkm_falcon *, काष्ठा nvkm_falcon_qmgr **);
व्योम nvkm_falcon_qmgr_del(काष्ठा nvkm_falcon_qmgr **);

प्रकार पूर्णांक
(*nvkm_falcon_qmgr_callback)(व्योम *priv, काष्ठा nvfw_falcon_msg *);

काष्ठा nvkm_falcon_cmdq;
पूर्णांक nvkm_falcon_cmdq_new(काष्ठा nvkm_falcon_qmgr *, स्थिर अक्षर *name,
			 काष्ठा nvkm_falcon_cmdq **);
व्योम nvkm_falcon_cmdq_del(काष्ठा nvkm_falcon_cmdq **);
व्योम nvkm_falcon_cmdq_init(काष्ठा nvkm_falcon_cmdq *,
			   u32 index, u32 offset, u32 size);
व्योम nvkm_falcon_cmdq_fini(काष्ठा nvkm_falcon_cmdq *);
पूर्णांक nvkm_falcon_cmdq_send(काष्ठा nvkm_falcon_cmdq *, काष्ठा nvfw_falcon_cmd *,
			  nvkm_falcon_qmgr_callback, व्योम *priv,
			  अचिन्हित दीर्घ समयout_jअगरfies);

काष्ठा nvkm_falcon_msgq;
पूर्णांक nvkm_falcon_msgq_new(काष्ठा nvkm_falcon_qmgr *, स्थिर अक्षर *name,
			 काष्ठा nvkm_falcon_msgq **);
व्योम nvkm_falcon_msgq_del(काष्ठा nvkm_falcon_msgq **);
व्योम nvkm_falcon_msgq_init(काष्ठा nvkm_falcon_msgq *,
			   u32 index, u32 offset, u32 size);
पूर्णांक nvkm_falcon_msgq_recv_iniपंचांगsg(काष्ठा nvkm_falcon_msgq *, व्योम *, u32 size);
व्योम nvkm_falcon_msgq_recv(काष्ठा nvkm_falcon_msgq *);
#पूर्ण_अगर
