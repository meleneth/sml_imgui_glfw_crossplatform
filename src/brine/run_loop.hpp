#pragma once

namespace brine {

class RunLoop {
public:
    virtual void run() = 0;
    virtual ~RunLoop() = default;
};

} // namespace brine
