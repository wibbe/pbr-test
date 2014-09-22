
#pragma once

#include <string>
#include <memory>
#include <vector>

namespace framework {

  namespace material { class BaseNode; }

  class Material
  {
    public:
      Material();
      virtual ~Material();

    private:
      std::vector<std::unique_ptr<material::BaseNode>> nodes_;
  };

  namespace material {
    class BaseNode
    {
      public:
        virtual ~BaseNode() { }

        virtual unsigned getConnections() const = 0;
        virtual void connect(unsigned slot, BaseNode * node) = 0;
    };

    template <unsigned ConnectionCount>
    class Vec4Node : public BaseNode
    {
      public:
        virtual ~Vec4Node() { }

        virtual void generateCode(std::string & header, std::string & body) = 0;

        unsigned getConnections() const { return ConnectionCount; }
        void connect(unsigned slot, BaseNode * node);

      private:
        BaseNode * connections_[ConnectionCount];
    };
  }

}