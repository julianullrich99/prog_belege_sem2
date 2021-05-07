#include <QWidget>

class QLabel;
class QPushButton;
class QLineEdit;
class QSlider;

class Window : public QWidget {
    Q_OBJECT

    public: 
        Window();
        virtual ~Window() {};
    
    private slots:
        void userEvent();
        void gameStateChangedEvent();
        void generateGameFieldEvent();
        void sliderChangedHandler();

    private:
        QLabel *testLabel;

        QPushButton *generateGamefieldButton;
        QPushButton *randomizeGamefieldButton;
        QPushButton *closeGamefieldButton;
        QPushButton *startSimulationButton;
        QPushButton *pauseSimulationButton;
        QPushButton *stepNextGenerationButton;

        QLabel *gamefieldSizeXLabel;
        QLabel *gamefieldSizeYLabel;
        QLineEdit *gamefieldSizeXInput;
        QLineEdit *gamefieldSizeYInput;

        QLabel *gamefieldFillPercentageLabel;
        QSlider *gamefieldFillPercentageSlider;
    
};


