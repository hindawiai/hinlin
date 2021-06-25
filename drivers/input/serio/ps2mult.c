<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TQC PS/2 Multiplexer driver
 *
 * Copyright (C) 2010 Dmitry Eremin-Solenikov
 */


#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/serपन.स>

MODULE_AUTHOR("Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>");
MODULE_DESCRIPTION("TQC PS/2 Multiplexer driver");
MODULE_LICENSE("GPL");

#घोषणा PS2MULT_KB_SELECTOR		0xA0
#घोषणा PS2MULT_MS_SELECTOR		0xA1
#घोषणा PS2MULT_ESCAPE			0x7D
#घोषणा PS2MULT_BSYNC			0x7E
#घोषणा PS2MULT_SESSION_START		0x55
#घोषणा PS2MULT_SESSION_END		0x56

काष्ठा ps2mult_port अणु
	काष्ठा serio *serio;
	अचिन्हित अक्षर sel;
	bool रेजिस्टरed;
पूर्ण;

#घोषणा PS2MULT_NUM_PORTS	2
#घोषणा PS2MULT_KBD_PORT	0
#घोषणा PS2MULT_MOUSE_PORT	1

काष्ठा ps2mult अणु
	काष्ठा serio *mx_serio;
	काष्ठा ps2mult_port ports[PS2MULT_NUM_PORTS];

	spinlock_t lock;
	काष्ठा ps2mult_port *in_port;
	काष्ठा ps2mult_port *out_port;
	bool escape;
पूर्ण;

/* First MUST come PS2MULT_NUM_PORTS selectors */
अटल स्थिर अचिन्हित अक्षर ps2mult_controls[] = अणु
	PS2MULT_KB_SELECTOR, PS2MULT_MS_SELECTOR,
	PS2MULT_ESCAPE, PS2MULT_BSYNC,
	PS2MULT_SESSION_START, PS2MULT_SESSION_END,
पूर्ण;

अटल स्थिर काष्ठा serio_device_id ps2mult_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_PS2MULT,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, ps2mult_serio_ids);

अटल व्योम ps2mult_select_port(काष्ठा ps2mult *psm, काष्ठा ps2mult_port *port)
अणु
	काष्ठा serio *mx_serio = psm->mx_serio;

	serio_ग_लिखो(mx_serio, port->sel);
	psm->out_port = port;
	dev_dbg(&mx_serio->dev, "switched to sel %02x\n", port->sel);
पूर्ण

अटल पूर्णांक ps2mult_serio_ग_लिखो(काष्ठा serio *serio, अचिन्हित अक्षर data)
अणु
	काष्ठा serio *mx_port = serio->parent;
	काष्ठा ps2mult *psm = serio_get_drvdata(mx_port);
	काष्ठा ps2mult_port *port = serio->port_data;
	bool need_escape;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&psm->lock, flags);

	अगर (psm->out_port != port)
		ps2mult_select_port(psm, port);

	need_escape = स_प्रथम(ps2mult_controls, data, माप(ps2mult_controls));

	dev_dbg(&serio->dev,
		"write: %s%02x\n", need_escape ? "ESC " : "", data);

	अगर (need_escape)
		serio_ग_लिखो(mx_port, PS2MULT_ESCAPE);

	serio_ग_लिखो(mx_port, data);

	spin_unlock_irqrestore(&psm->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ps2mult_serio_start(काष्ठा serio *serio)
अणु
	काष्ठा ps2mult *psm = serio_get_drvdata(serio->parent);
	काष्ठा ps2mult_port *port = serio->port_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&psm->lock, flags);
	port->रेजिस्टरed = true;
	spin_unlock_irqrestore(&psm->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम ps2mult_serio_stop(काष्ठा serio *serio)
अणु
	काष्ठा ps2mult *psm = serio_get_drvdata(serio->parent);
	काष्ठा ps2mult_port *port = serio->port_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&psm->lock, flags);
	port->रेजिस्टरed = false;
	spin_unlock_irqrestore(&psm->lock, flags);
पूर्ण

अटल पूर्णांक ps2mult_create_port(काष्ठा ps2mult *psm, पूर्णांक i)
अणु
	काष्ठा serio *mx_serio = psm->mx_serio;
	काष्ठा serio *serio;

	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!serio)
		वापस -ENOMEM;

	strlcpy(serio->name, "TQC PS/2 Multiplexer", माप(serio->name));
	snम_लिखो(serio->phys, माप(serio->phys),
		 "%s/port%d", mx_serio->phys, i);
	serio->id.type = SERIO_8042;
	serio->ग_लिखो = ps2mult_serio_ग_लिखो;
	serio->start = ps2mult_serio_start;
	serio->stop = ps2mult_serio_stop;
	serio->parent = psm->mx_serio;
	serio->port_data = &psm->ports[i];

	psm->ports[i].serio = serio;

	वापस 0;
पूर्ण

अटल व्योम ps2mult_reset(काष्ठा ps2mult *psm)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&psm->lock, flags);

	serio_ग_लिखो(psm->mx_serio, PS2MULT_SESSION_END);
	serio_ग_लिखो(psm->mx_serio, PS2MULT_SESSION_START);

	ps2mult_select_port(psm, &psm->ports[PS2MULT_KBD_PORT]);

	spin_unlock_irqrestore(&psm->lock, flags);
पूर्ण

अटल पूर्णांक ps2mult_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा ps2mult *psm;
	पूर्णांक i;
	पूर्णांक error;

	अगर (!serio->ग_लिखो)
		वापस -EINVAL;

	psm = kzalloc(माप(*psm), GFP_KERNEL);
	अगर (!psm)
		वापस -ENOMEM;

	spin_lock_init(&psm->lock);
	psm->mx_serio = serio;

	क्रम (i = 0; i < PS2MULT_NUM_PORTS; i++) अणु
		psm->ports[i].sel = ps2mult_controls[i];
		error = ps2mult_create_port(psm, i);
		अगर (error)
			जाओ err_out;
	पूर्ण

	psm->in_port = psm->out_port = &psm->ports[PS2MULT_KBD_PORT];

	serio_set_drvdata(serio, psm);
	error = serio_खोलो(serio, drv);
	अगर (error)
		जाओ err_out;

	ps2mult_reset(psm);

	क्रम (i = 0; i <  PS2MULT_NUM_PORTS; i++) अणु
		काष्ठा serio *s = psm->ports[i].serio;

		dev_info(&serio->dev, "%s port at %s\n", s->name, serio->phys);
		serio_रेजिस्टर_port(s);
	पूर्ण

	वापस 0;

err_out:
	जबतक (--i >= 0)
		kमुक्त(psm->ports[i].serio);
	kमुक्त(psm);
	वापस error;
पूर्ण

अटल व्योम ps2mult_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा ps2mult *psm = serio_get_drvdata(serio);

	/* Note that serio core alपढ़ोy take care of children ports */
	serio_ग_लिखो(serio, PS2MULT_SESSION_END);
	serio_बंद(serio);
	kमुक्त(psm);

	serio_set_drvdata(serio, शून्य);
पूर्ण

अटल पूर्णांक ps2mult_reconnect(काष्ठा serio *serio)
अणु
	काष्ठा ps2mult *psm = serio_get_drvdata(serio);

	ps2mult_reset(psm);

	वापस 0;
पूर्ण

अटल irqवापस_t ps2mult_पूर्णांकerrupt(काष्ठा serio *serio,
				     अचिन्हित अक्षर data, अचिन्हित पूर्णांक dfl)
अणु
	काष्ठा ps2mult *psm = serio_get_drvdata(serio);
	काष्ठा ps2mult_port *in_port;
	अचिन्हित दीर्घ flags;

	dev_dbg(&serio->dev, "Received %02x flags %02x\n", data, dfl);

	spin_lock_irqsave(&psm->lock, flags);

	अगर (psm->escape) अणु
		psm->escape = false;
		in_port = psm->in_port;
		अगर (in_port->रेजिस्टरed)
			serio_पूर्णांकerrupt(in_port->serio, data, dfl);
		जाओ out;
	पूर्ण

	चयन (data) अणु
	हाल PS2MULT_ESCAPE:
		dev_dbg(&serio->dev, "ESCAPE\n");
		psm->escape = true;
		अवरोध;

	हाल PS2MULT_BSYNC:
		dev_dbg(&serio->dev, "BSYNC\n");
		psm->in_port = psm->out_port;
		अवरोध;

	हाल PS2MULT_SESSION_START:
		dev_dbg(&serio->dev, "SS\n");
		अवरोध;

	हाल PS2MULT_SESSION_END:
		dev_dbg(&serio->dev, "SE\n");
		अवरोध;

	हाल PS2MULT_KB_SELECTOR:
		dev_dbg(&serio->dev, "KB\n");
		psm->in_port = &psm->ports[PS2MULT_KBD_PORT];
		अवरोध;

	हाल PS2MULT_MS_SELECTOR:
		dev_dbg(&serio->dev, "MS\n");
		psm->in_port = &psm->ports[PS2MULT_MOUSE_PORT];
		अवरोध;

	शेष:
		in_port = psm->in_port;
		अगर (in_port->रेजिस्टरed)
			serio_पूर्णांकerrupt(in_port->serio, data, dfl);
		अवरोध;
	पूर्ण

 out:
	spin_unlock_irqrestore(&psm->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा serio_driver ps2mult_drv = अणु
	.driver		= अणु
		.name	= "ps2mult",
	पूर्ण,
	.description	= "TQC PS/2 Multiplexer driver",
	.id_table	= ps2mult_serio_ids,
	.पूर्णांकerrupt	= ps2mult_पूर्णांकerrupt,
	.connect	= ps2mult_connect,
	.disconnect	= ps2mult_disconnect,
	.reconnect	= ps2mult_reconnect,
पूर्ण;

module_serio_driver(ps2mult_drv);
