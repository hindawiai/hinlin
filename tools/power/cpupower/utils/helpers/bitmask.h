<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CPUPOWER_BITMASK__
#घोषणा __CPUPOWER_BITMASK__

/* Taken over from libbiपंचांगask, a project initiated from sgi:
 * Url:            http://oss.sgi.com/projects/cpusets/
 * Unक्रमtunately it's not very widespपढ़ो, thereक्रमe relevant parts are
 * pasted here.
 */

काष्ठा biपंचांगask अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित दीर्घ *maskp;
पूर्ण;

काष्ठा biपंचांगask *biपंचांगask_alloc(अचिन्हित पूर्णांक n);
व्योम biपंचांगask_मुक्त(काष्ठा biपंचांगask *bmp);

काष्ठा biपंचांगask *biपंचांगask_setbit(काष्ठा biपंचांगask *bmp, अचिन्हित पूर्णांक i);
काष्ठा biपंचांगask *biपंचांगask_setall(काष्ठा biपंचांगask *bmp);
काष्ठा biपंचांगask *biपंचांगask_clearall(काष्ठा biपंचांगask *bmp);

अचिन्हित पूर्णांक biपंचांगask_first(स्थिर काष्ठा biपंचांगask *bmp);
अचिन्हित पूर्णांक biपंचांगask_next(स्थिर काष्ठा biपंचांगask *bmp, अचिन्हित पूर्णांक i);
अचिन्हित पूर्णांक biपंचांगask_last(स्थिर काष्ठा biपंचांगask *bmp);
पूर्णांक biपंचांगask_isallclear(स्थिर काष्ठा biपंचांगask *bmp);
पूर्णांक biपंचांगask_isbitset(स्थिर काष्ठा biपंचांगask *bmp, अचिन्हित पूर्णांक i);

पूर्णांक biपंचांगask_parselist(स्थिर अक्षर *buf, काष्ठा biपंचांगask *bmp);
पूर्णांक biपंचांगask_displaylist(अक्षर *buf, पूर्णांक len, स्थिर काष्ठा biपंचांगask *bmp);



#पूर्ण_अगर /*__CPUPOWER_BITMASK__ */
