<शैली गुरु>
/*
 *
 * BRIEF MODULE DESCRIPTION
 *      Board specअगरic pci fixups क्रम the Toshiba rbtx4927
 *
 * Copyright 2001 MontaVista Software Inc.
 * Author: MontaVista Software, Inc.
 *              ppopov@mvista.com or source@mvista.com
 *
 * Copyright (C) 2000-2001 Toshiba Corporation
 *
 * Copyright (C) 2004 MontaVista Software Inc.
 * Author: Manish Lachwani (mlachwani@mvista.com)
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */
#समावेश <linux/types.h>
#समावेश <यंत्र/txx9/pci.h>
#समावेश <यंत्र/txx9/rbtx4927.h>

पूर्णांक rbtx4927_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अचिन्हित अक्षर irq = pin;

	/* IRQ rotation */
	irq--;			/* 0-3 */
	अगर (slot == TX4927_PCIC_IDSEL_AD_TO_SLOT(23)) अणु
		/* PCI CardSlot (IDSEL=A23) */
		/* PCIA => PCIA */
		irq = (irq + 0 + slot) % 4;
	पूर्ण अन्यथा अणु
		/* PCI Backplane */
		अगर (txx9_pci_option & TXX9_PCI_OPT_PICMG)
			irq = (irq + 33 - slot) % 4;
		अन्यथा
			irq = (irq + 3 + slot) % 4;
	पूर्ण
	irq++;	/* 1-4 */

	चयन (irq) अणु
	हाल 1:
		irq = RBTX4927_IRQ_IOC_PCIA;
		अवरोध;
	हाल 2:
		irq = RBTX4927_IRQ_IOC_PCIB;
		अवरोध;
	हाल 3:
		irq = RBTX4927_IRQ_IOC_PCIC;
		अवरोध;
	हाल 4:
		irq = RBTX4927_IRQ_IOC_PCID;
		अवरोध;
	पूर्ण
	वापस irq;
पूर्ण
