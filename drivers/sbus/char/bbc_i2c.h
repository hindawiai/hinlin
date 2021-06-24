<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BBC_I2C_H
#घोषणा _BBC_I2C_H

#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/list.h>

काष्ठा bbc_i2c_client अणु
	काष्ठा bbc_i2c_bus		*bp;
	काष्ठा platक्रमm_device		*op;
	पूर्णांक				bus;
	पूर्णांक				address;
पूर्ण;

क्रमागत fan_action अणु FAN_SLOWER, FAN_SAME, FAN_FASTER, FAN_FULLBLAST, FAN_STATE_MAX पूर्ण;

काष्ठा bbc_cpu_temperature अणु
	काष्ठा list_head		bp_list;
	काष्ठा list_head		glob_list;

	काष्ठा bbc_i2c_client		*client;
	पूर्णांक				index;

	/* Current पढ़ोings, and history. */
	s8				curr_cpu_temp;
	s8				curr_amb_temp;
	s8				prev_cpu_temp;
	s8				prev_amb_temp;
	s8				avg_cpu_temp;
	s8				avg_amb_temp;

	पूर्णांक				sample_tick;

	क्रमागत fan_action			fan_toकरो[2];
#घोषणा FAN_AMBIENT	0
#घोषणा FAN_CPU		1
पूर्ण;

काष्ठा bbc_fan_control अणु
	काष्ठा list_head		bp_list;
	काष्ठा list_head		glob_list;

	काष्ठा bbc_i2c_client 		*client;
	पूर्णांक 				index;

	पूर्णांक				psupply_fan_on;
	पूर्णांक				cpu_fan_speed;
	पूर्णांक				प्रणाली_fan_speed;
पूर्ण;

#घोषणा NUM_CHILDREN	8

काष्ठा bbc_i2c_bus अणु
	काष्ठा bbc_i2c_bus		*next;
	पूर्णांक				index;
	spinlock_t			lock;
	व्योम				__iomem *i2c_bussel_reg;
	व्योम				__iomem *i2c_control_regs;
	अचिन्हित अक्षर			own, घड़ी;

	रुको_queue_head_t		wq;
	अस्थिर पूर्णांक			रुकोing;

	काष्ठा list_head		temps;
	काष्ठा list_head		fans;

	काष्ठा platक्रमm_device		*op;
	काष्ठा अणु
		काष्ठा platक्रमm_device	*device;
		पूर्णांक			client_claimed;
	पूर्ण devs[NUM_CHILDREN];
पूर्ण;

/* Probing and attachment. */
बाह्य काष्ठा platक्रमm_device *bbc_i2c_getdev(काष्ठा bbc_i2c_bus *, पूर्णांक);
बाह्य काष्ठा bbc_i2c_client *bbc_i2c_attach(काष्ठा bbc_i2c_bus *bp, काष्ठा platक्रमm_device *);
बाह्य व्योम bbc_i2c_detach(काष्ठा bbc_i2c_client *);

/* Register पढ़ो/ग_लिखो.  NOTE: Blocking! */
बाह्य पूर्णांक bbc_i2c_ग_लिखोb(काष्ठा bbc_i2c_client *, अचिन्हित अक्षर val, पूर्णांक off);
बाह्य पूर्णांक bbc_i2c_पढ़ोb(काष्ठा bbc_i2c_client *, अचिन्हित अक्षर *byte, पूर्णांक off);
बाह्य पूर्णांक bbc_i2c_ग_लिखो_buf(काष्ठा bbc_i2c_client *, अक्षर *buf, पूर्णांक len, पूर्णांक off);
बाह्य पूर्णांक bbc_i2c_पढ़ो_buf(काष्ठा bbc_i2c_client *, अक्षर *buf, पूर्णांक len, पूर्णांक off);

#पूर्ण_अगर /* _BBC_I2C_H */
