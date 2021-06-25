<शैली गुरु>
/*
	Hardware Ranकरोm Number Generator

	Please पढ़ो Documentation/admin-guide/hw_अक्रमom.rst क्रम details on use.

	----------------------------------------------------------
	This software may be used and distributed according to the terms
        of the GNU General Public License, incorporated herein by reference.

 */

#अगर_अघोषित LINUX_HWRANDOM_H_
#घोषणा LINUX_HWRANDOM_H_

#समावेश <linux/completion.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/kref.h>

/**
 * काष्ठा hwrng - Hardware Ranकरोm Number Generator driver
 * @name:		Unique RNG name.
 * @init:		Initialization callback (can be शून्य).
 * @cleanup:		Cleanup callback (can be शून्य).
 * @data_present:	Callback to determine अगर data is available
 *			on the RNG. If शून्य, it is assumed that
 *			there is always data available.  *OBSOLETE*
 * @data_पढ़ो:		Read data from the RNG device.
 *			Returns the number of lower अक्रमom bytes in "data".
 *			Must not be शून्य.    *OBSOLETE*
 * @पढ़ो:		New API. drivers can fill up to max bytes of data
 *			पूर्णांकo the buffer. The buffer is aligned क्रम any type
 *			and max is a multiple of 4 and >= 32 bytes.
 * @priv:		Private data, क्रम use by the RNG driver.
 * @quality:		Estimation of true entropy in RNG's bitstream
 *			(in bits of entropy per 1024 bits of input;
 *			valid values: 1 to 1024, or 0 क्रम unknown).
 */
काष्ठा hwrng अणु
	स्थिर अक्षर *name;
	पूर्णांक (*init)(काष्ठा hwrng *rng);
	व्योम (*cleanup)(काष्ठा hwrng *rng);
	पूर्णांक (*data_present)(काष्ठा hwrng *rng, पूर्णांक रुको);
	पूर्णांक (*data_पढ़ो)(काष्ठा hwrng *rng, u32 *data);
	पूर्णांक (*पढ़ो)(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको);
	अचिन्हित दीर्घ priv;
	अचिन्हित लघु quality;

	/* पूर्णांकernal. */
	काष्ठा list_head list;
	काष्ठा kref ref;
	काष्ठा completion cleanup_करोne;
पूर्ण;

काष्ठा device;

/** Register a new Hardware Ranकरोm Number Generator driver. */
बाह्य पूर्णांक hwrng_रेजिस्टर(काष्ठा hwrng *rng);
बाह्य पूर्णांक devm_hwrng_रेजिस्टर(काष्ठा device *dev, काष्ठा hwrng *rng);
/** Unरेजिस्टर a Hardware Ranकरोm Number Generator driver. */
बाह्य व्योम hwrng_unरेजिस्टर(काष्ठा hwrng *rng);
बाह्य व्योम devm_hwrng_unरेजिस्टर(काष्ठा device *dve, काष्ठा hwrng *rng);
/** Feed अक्रमom bits पूर्णांकo the pool. */
बाह्य व्योम add_hwgenerator_अक्रमomness(स्थिर अक्षर *buffer, माप_प्रकार count, माप_प्रकार entropy);

#पूर्ण_अगर /* LINUX_HWRANDOM_H_ */
