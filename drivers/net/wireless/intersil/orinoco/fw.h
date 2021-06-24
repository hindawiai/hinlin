<शैली गुरु>
/* Firmware file पढ़ोing and करोwnload helpers
 *
 * See copyright notice in मुख्य.c
 */
#अगर_अघोषित _ORINOCO_FW_H_
#घोषणा _ORINOCO_FW_H_

/* Forward declations */
काष्ठा orinoco_निजी;

पूर्णांक orinoco_करोwnload(काष्ठा orinoco_निजी *priv);

#अगर defined(CONFIG_HERMES_CACHE_FW_ON_INIT) || defined(CONFIG_PM_SLEEP)
व्योम orinoco_cache_fw(काष्ठा orinoco_निजी *priv, पूर्णांक ap);
व्योम orinoco_uncache_fw(काष्ठा orinoco_निजी *priv);
#अन्यथा
#घोषणा orinoco_cache_fw(priv, ap) करो अणु पूर्ण जबतक (0)
#घोषणा orinoco_uncache_fw(priv) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* _ORINOCO_FW_H_ */
