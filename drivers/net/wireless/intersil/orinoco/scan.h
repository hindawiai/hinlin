<शैली गुरु>
/* Helpers क्रम managing scan queues
 *
 * See copyright notice in मुख्य.c
 */
#अगर_अघोषित _ORINOCO_SCAN_H_
#घोषणा _ORINOCO_SCAN_H_

/* Forward declarations */
काष्ठा orinoco_निजी;
काष्ठा agere_ext_scan_info;

/* Add scan results */
व्योम orinoco_add_extscan_result(काष्ठा orinoco_निजी *priv,
				काष्ठा agere_ext_scan_info *atom,
				माप_प्रकार len);
व्योम orinoco_add_hostscan_results(काष्ठा orinoco_निजी *dev,
				  अचिन्हित अक्षर *buf,
				  माप_प्रकार len);
व्योम orinoco_scan_करोne(काष्ठा orinoco_निजी *priv, bool पात);

#पूर्ण_अगर /* _ORINOCO_SCAN_H_ */
