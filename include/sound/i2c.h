<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_I2C_H
#घोषणा __SOUND_I2C_H

/*
 */

#घोषणा SND_I2C_DEVICE_ADDRTEN	(1<<0)	/* 10-bit I2C address */

काष्ठा snd_i2c_device अणु
	काष्ठा list_head list;
	काष्ठा snd_i2c_bus *bus;	/* I2C bus */
	अक्षर name[32];		/* some useful device name */
	अचिन्हित लघु flags;	/* device flags */
	अचिन्हित लघु addr;	/* device address (might be 10-bit) */
	अचिन्हित दीर्घ निजी_value;
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा snd_i2c_device *device);
पूर्ण;

#घोषणा snd_i2c_device(n) list_entry(n, काष्ठा snd_i2c_device, list)

काष्ठा snd_i2c_bit_ops अणु
	व्योम (*start)(काष्ठा snd_i2c_bus *bus);	/* transfer start */
	व्योम (*stop)(काष्ठा snd_i2c_bus *bus);	/* transfer stop */
	व्योम (*direction)(काष्ठा snd_i2c_bus *bus, पूर्णांक घड़ी, पूर्णांक data);  /* set line direction (0 = ग_लिखो, 1 = पढ़ो) */
	व्योम (*setlines)(काष्ठा snd_i2c_bus *bus, पूर्णांक घड़ी, पूर्णांक data);
	पूर्णांक (*अ_लोlock)(काष्ठा snd_i2c_bus *bus);
	पूर्णांक (*getdata)(काष्ठा snd_i2c_bus *bus, पूर्णांक ack);
पूर्ण;

काष्ठा snd_i2c_ops अणु
	पूर्णांक (*sendbytes)(काष्ठा snd_i2c_device *device, अचिन्हित अक्षर *bytes, पूर्णांक count);
	पूर्णांक (*पढ़ोbytes)(काष्ठा snd_i2c_device *device, अचिन्हित अक्षर *bytes, पूर्णांक count);
	पूर्णांक (*probeaddr)(काष्ठा snd_i2c_bus *bus, अचिन्हित लघु addr);
पूर्ण;

काष्ठा snd_i2c_bus अणु
	काष्ठा snd_card *card;	/* card which I2C beदीर्घs to */
	अक्षर name[32];		/* some useful label */

	काष्ठा mutex lock_mutex;

	काष्ठा snd_i2c_bus *master;	/* master bus when SCK/SCL is shared */
	काष्ठा list_head buses;	/* master: slave buses sharing SCK/SCL, slave: link list */

	काष्ठा list_head devices; /* attached devices to this bus */

	जोड़ अणु
		काष्ठा snd_i2c_bit_ops *bit;
		व्योम *ops;
	पूर्ण hw_ops;		/* lowlevel operations */
	स्थिर काष्ठा snd_i2c_ops *ops;	/* midlevel operations */

	अचिन्हित दीर्घ निजी_value;
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा snd_i2c_bus *bus);
पूर्ण;

#घोषणा snd_i2c_slave_bus(n) list_entry(n, काष्ठा snd_i2c_bus, buses)

पूर्णांक snd_i2c_bus_create(काष्ठा snd_card *card, स्थिर अक्षर *name,
		       काष्ठा snd_i2c_bus *master, काष्ठा snd_i2c_bus **ri2c);
पूर्णांक snd_i2c_device_create(काष्ठा snd_i2c_bus *bus, स्थिर अक्षर *name,
			  अचिन्हित अक्षर addr, काष्ठा snd_i2c_device **rdevice);
पूर्णांक snd_i2c_device_मुक्त(काष्ठा snd_i2c_device *device);

अटल अंतरभूत व्योम snd_i2c_lock(काष्ठा snd_i2c_bus *bus)
अणु
	अगर (bus->master)
		mutex_lock(&bus->master->lock_mutex);
	अन्यथा
		mutex_lock(&bus->lock_mutex);
पूर्ण

अटल अंतरभूत व्योम snd_i2c_unlock(काष्ठा snd_i2c_bus *bus)
अणु
	अगर (bus->master)
		mutex_unlock(&bus->master->lock_mutex);
	अन्यथा
		mutex_unlock(&bus->lock_mutex);
पूर्ण

पूर्णांक snd_i2c_sendbytes(काष्ठा snd_i2c_device *device, अचिन्हित अक्षर *bytes, पूर्णांक count);
पूर्णांक snd_i2c_पढ़ोbytes(काष्ठा snd_i2c_device *device, अचिन्हित अक्षर *bytes, पूर्णांक count);
पूर्णांक snd_i2c_probeaddr(काष्ठा snd_i2c_bus *bus, अचिन्हित लघु addr);

#पूर्ण_अगर /* __SOUND_I2C_H */
