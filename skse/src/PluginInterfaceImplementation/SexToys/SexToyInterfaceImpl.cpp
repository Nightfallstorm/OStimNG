#include "SexToyInterfaceImpl.h"

#include "SexToys/ToyTable.h"

namespace Interface {
    uint32_t SexToyInterfaceImpl::getVersion() {
        return 1;
    }

    void SexToyInterfaceImpl::registerReloadListener(OStim::SexToyReloadListener* listener) {
        Toys::ToyTable::getSingleton()->addReloadListener(listener);
    }

    void SexToyInterfaceImpl::addToy(OStim::SexToy* toy) {
        Toys::ToyTable::getSingleton()->addToy(toy);
    }
}